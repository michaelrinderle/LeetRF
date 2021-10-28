#include <iostream>
#include "gtest/gtest.h"
#include "../src/device_hackrf.h"


#define DEFAULT_SAMPLE_RATE_HZ 256000
#define RADIO_FREQ 95300000
#define OUTPUT_FILE "output_samples.raw"


int 
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    device_hackrf sdr;
    /*ASSERT_TRUE(sdr.load());
    ASSERT_TRUE(sdr.set_frequency(RADIO_FREQ));
    ASSERT_TRUE(sdr.set_sample_rate(DEFAULT_SAMPLE_RATE_HZ));
    ASSERT_TRUE(sdr.rx_frequency(15));
    ASSERT_TRUE(sdr.unload());*/
    
    return RUN_ALL_TESTS();
}