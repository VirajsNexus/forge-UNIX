//file name Copy_file_by_child_process.c

#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
    int src_fd;
    int dst_fd;
    char buffer[100];
    int n_read;
    
    //argument check
    if(argc !=3 )
    {
        write(2, "Invalid arguments entered \n", 28);
        _exit(1);
    }
    
    if(fork() ==0)
    {
    //open source file
    src_fd = open(argv[1], O_RDONLY);
    
    if(src_fd == -1)
    {
        write(2, "Error : Source file not found \n", 32);
        _exit(1);
    }

    
    //create file
    dst_fd = creat(argv[2], 0644);
    if(dst_fd == -1)
    {
        write(2, "ERROR : Unable to create destination file.\n", 33);
        close(src_fd);
        _exit(1);
    }
    
    // copy data
    while((n_read = read(src_fd, buffer, 100)) > 0)
    {
        if(write(dst_fd, buffer, n_read) != n_read)
        {
            write(2, "ERROR : Write operation failed \n", 33);
            close(src_fd);
            close(dst_fd);
            _exit(1);
        }
    }
    
    //Final : Release final files
    close(src_fd);
    close(dst_fd);
    
    //success message
    write(1, "Copy Operation Successful\n\n", 28);
    
    _exit(0);
    }
    
    else
    {
      wait(NULL);
      write(2, "Parent says: Child is finished...\n", 35);
    }
}
