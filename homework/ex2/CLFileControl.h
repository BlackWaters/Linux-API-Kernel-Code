#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#define M_END 1 
#define M_SET 0


class CLFileControl
{
	public:
		int ReadFile(int ReadCount)
		{
			if (Fd_id==-1) return -1;

			if (Flush()==-1) return -1;

			if (ReadCount<=ReadBufCount) 
			{
				for (int i=0;i<ReadCount;i++) printf("%c",ReadBuf[i]);
				puts("");
				return 0;

			}

			if (SetPos(ReadBufCount,M_SET)==-1) return -1;

			int UnreadCount=ReadCount-ReadBufCount;
			char *Buf=(char *)malloc(sizeof(char)*UnreadCount );

			if (read(Fd_id,Buf,UnreadCount)==-1)
			{
				printf("Read error.\n");
				return -1;
			}

			memcpy(ReadBuf+ReadBufCount,Buf,UnreadCount);

			ReadBufCount=ReadCount;
			printf("%s\n",ReadBuf);
			return 0;

		}

		int WriteFile(char *Msg)
		{
			if (Fd_id==-1) return -1;

			int UnusedBufCount=4096-WriteBufCount,len=strlen(Msg);
			if (len > UnusedBufCount) 
			{
				if (Flush()==-1) return -1;
				if (SetPos(0,M_END)==-1) return -1;
				if (write(Fd_id,Msg,len)==-1) 
				{
					printf("Write Massege error.\n");
					return -1;
				}
				return 0;
			}

			memcpy(WriteBuf+WriteBufCount,Msg,len);
			WriteBufCount+=len;
			return 0;
		}

		CLFileControl() 
		{
			Fd_id=-1;
			ReadBuf=(char *)malloc(sizeof(char)*4096);
			ReadBufCount=0;
			WriteBuf=(char *)malloc(sizeof(char)*4096);
			WriteBufCount=0;
		}
		CLFileControl(char *FilePath)
		{
			
			Fd_id=-1;
			ReadBuf=(char *)malloc(sizeof(char)*4096);
			ReadBufCount=0;
			WriteBuf=(char *)malloc(sizeof(char)*4096);
			WriteBufCount=0;
			
			//this->CLFileControl();
			OpenFile(FilePath);
		}
		~CLFileControl() { Flush(); delete []ReadBuf;  delete []WriteBuf; }


	private:
		int OpenFile(char *FilePath)
		{
			Fd_id=open(FilePath,O_RDWR);
			if (Fd_id==-1)
			{
				printf("Open error.\n");
				return -1;
			}
			return 0;
		}

		int SetPos(int p,int Flag)
		{
			if (Fd_id==-1) 
			{
				printf("File hasn't been opened.\n");
				return -1;
			}
			if (Flag==0)
				if (lseek(Fd_id,p,SEEK_SET)==-1) 
				{
					printf("Lseek error.\n");
					return -1;
				} 
				else ;
			else 
				if (lseek(Fd_id,p,SEEK_END)==-1)
				{
					printf("Lseek error.\n");
					return -1;
				}
			return 0;
		}

		int Flush()
		{
			if (WriteBufCount==0) return 0;
			if (SetPos(0,M_END)==-1) return -1;
			if (write(Fd_id,WriteBuf,WriteBufCount)==-1) 
			{
				printf("Write buffer error.\n");
				return -1;
			}
			memset(WriteBuf,0,sizeof(WriteBuf));
			WriteBufCount=0;
			return 0;
		}

		char *ReadBuf,*WriteBuf; int ReadBufCount,WriteBufCount;
		int Fd_id;
};
