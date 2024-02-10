// User space program 

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
        int fd,len;
        char arr[100];
        char ker[100];
        printf("Enter the string...\n");
        scanf("%[^\n]%*c",arr);

        //the file open here 

        fd=open("/dev/SKRJS_devices",O_RDWR);

        if(fd<0)
        {
                perror("open:");
                return fd;
        }
        else
        {
                len = strlen(arr);
                printf("file is opened\n");
                //User space data send to Kernal space 
                write(fd,arr,len + 1);
                printf("user data send successfully send it: %s\n",arr);

                //Get kernal data to user space


                int retur = read(fd,ker,len+1);
                 printf("The data recived from kernal:%s\n",ker);
		  printf("The return values : %d\n",retur);
        }

        //The file close here 
        close(fd);
        printf("file is closed \n");


        return 0;
}                                                                                                         
                                                                                                                                                  
                                                                              


