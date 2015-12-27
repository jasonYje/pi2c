#include "pi2c.h"

#include <cerrno>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#pragma GCC diagnostic ignored "-fpermissive"
#pragma GCC diagnostic ignored "-pedantic"

Pi2c::Pi2c()
: m_handle(-1)
, m_address(0)
{

}

Pi2c::~Pi2c()
{
	if (m_handle)
		close(m_handle);
}

bool Pi2c::initialize(int address, bool revision /* = 1 */)
{
	char device[11] = "/dev/i2c-X";
	if (revision == 1) 
		device[9] = '1';
	else
		device[9] = '0';
	
	m_handle = open(device, O_RDWR | O_SYNC);
	if (m_handle < 0)
		return false;
	
	m_is_connect = (ioctl(m_handle, I2C_SLAVE, address) == 0);
	if (m_is_connect)
		m_address = address;
	return m_is_connect;
}

void Pi2c::status()
{
    std::cout << "slave: 0x" << std::hex << m_address << std::endl;
	std::cout << "handle:" << m_handle << std::endl;
	std::cout << "connect:" << std::boolalpha << m_is_connect << std::endl;
}

bool Pi2c::is_connect() const
{
	return m_is_connect;
}

int  Pi2c::read_block(char* data, int length)
{
    const int er = read(m_handle, data, length);
    return er;
}

int  Pi2c::write_block(char* data, int length)
{
    const int er = write(m_handle, data, length);
    return er;
}
