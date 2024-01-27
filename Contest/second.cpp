#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

int main()
{
    std::string shm_name;
    std::getline(std::cin, shm_name);
    
    if(shm_name[0] != '/')
    {
        std::cout << shm_name << '\n';
        return 1;
    }
    
    int fd = shm_open(shm_name.c_str(), O_CREAT | O_RDWR, 0644);    
    if(fd == -1)
    {
        std::cout << "Error code: " << errno << '\n' << "\x1b[0m";
        perror("\x1b[31mshm_open");
        close(fd);
        shm_unlink(shm_name.c_str());
        return 1;
    }
    
    if(ftruncate(fd, 1000) == -1)
    {
        std::cout << "\x1b[31mError code: " << errno << '\n' << "\x1b[0m";
        perror("\x1b[31mftruncate");
        close(fd);
        shm_unlink(shm_name.c_str());
        return 1;
    }

    char *message = (char*)mmap(0, 1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(errno != 0)
    {
        std::cout << "Error code: " << errno << '\n' << "\x1b[0m";
        perror("\x1b[31mmmap");
        return 1;
    }
    
    std::cout << message << '\n';
    
    munmap(message, 1000);
    close(fd);
    shm_unlink(shm_name.c_str());
}
