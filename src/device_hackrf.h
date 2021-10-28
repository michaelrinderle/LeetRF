#ifndef DEVICE_HACKRF_H
#define DEVICE_HACKRF_H

#include "../include/hackrf/hackrf.h"

#define DEFAULT_SAMPLE_RATE_HZ 256000
#define RADIO_FREQ 95300000
#define OUTPUT_FILE "output_samples.raw"

class device_hackrf {

public:

	std::string get_device_name();
	bool load();
	bool unload();
	bool set_frequency(uint64_t freq_hz);
	bool set_sample_rate(double sample_rate);
	bool rx_frequency(int seconds);
	int rx_callback(hackrf_transfer* transfer);

private:

	static int rx_callback(hackrf_transfer* transfer);

	hackrf_device* device;
	char* serial_number;
	uint64_t freq_hz;
	double sample_rate;
	int cmd_result;	
};

#endif // DEVICE_HACKRF_H
