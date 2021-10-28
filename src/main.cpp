#include "stdfx.h"
#include "device_hackrf.h"

int
main(int argc, char* argv[]) {
	device_hackrf device;
	device.load();
	auto name = device.get_device_name();
	std::cout << name << std::endl;
	device.unload();
	return 0;
}