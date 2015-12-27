#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>    
#include <unistd.h>   
#include <sys/ioctl.h>

class Pi2c
{
public:
	Pi2c();
	~Pi2c();
	
	bool initialize(int address, bool revision = 1);
	void status();
	bool is_connect() const;
    int  read_block(char* data, int length);
    int  write_block(char* data, int length);

private:
	int  m_address;
	int  m_handle;
	bool m_is_connect;
};