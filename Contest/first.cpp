#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main()
{
    auto shm_name = "/my_shm";
    
    int fd = shm_open(shm_name, O_CREAT | O_RDWR, 0644);    
    if(fd == -1)
    {
        std::cout << "Error code: " << errno << "\x1b[0m";
        perror("\x1b[31mshm_open");
        close(fd);
        shm_unlink(shm_name);
        return 1;
    }
    
    if(ftruncate(fd, 1000) == -1)
    {
        std::cout << "Error code: " << errno << "\x1b[0m";
        perror("\x1b[31mftruncate");
        close(fd);
        shm_unlink(shm_name);
        return 1;
    }
    
    char *message = (char*)mmap(0, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(message, "Hello world");
    
    if(errno != 0)
    {
        std::cout << "Error code: " << errno << "\x1b[0m";
        perror("\x1b[31mmmap");
        return 1;
    }
    
    std::cout << shm_name;
    
    munmap(message, 1000);
    close(fd);
    return 0;
}
