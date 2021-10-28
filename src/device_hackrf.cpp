#include "stdfx.h"
#include "device_hackrf.h"

using namespace std;

static FILE* fp;

bool device_hackrf::load()
{
    // load hackrf
    cmd_result = hackrf_init();
    if (cmd_result != HACKRF_SUCCESS)
    {
        cout << "[*] hackrf initialization unsuccessful" << endl;
        return EXIT_FAILURE;
    }

    // locate & open device
    auto devices = hackrf_device_list();
    serial_number = devices[0].serial_numbers[0];

    cmd_result = hackrf_open_by_serial(serial_number, &device);
    if (cmd_result != HACKRF_SUCCESS)
    {
        cout << "[*] hackrf initialization unsuccessful" << endl;
        return EXIT_FAILURE;
    }

    cout << "[*] hackrf SN#" << serial_number << " initialized" << endl;

    fp = fopen(OUTPUT_FILE, "w");
    if (fp == nullptr) {
        cout << "[*] hackrf no audio file will be saved" << endl;
    }

    cout << "[*] hackrf initialized" << endl;
    return true;
}

bool device_hackrf::unload() {
    // unload hackrf
    if (device != nullptr) {
        cmd_result = hackrf_close(device);
        if (cmd_result != HACKRF_SUCCESS)
        {
            cout << "[*] hackrf unloaded unsuccessfully" << endl;
            return EXIT_FAILURE;
        }
    }

    // clean up
    hackrf_exit();

    // close raw file
    if (fp != nullptr) {
        fclose(fp);
    }

    cout << "[*] hackrf unloaded" << endl;
    return true;
}

string device_hackrf::get_device_name()
{
    return string(serial_number);
}

bool device_hackrf::set_frequency(uint64_t freq_hz) {
    device_hackrf::freq_hz = freq_hz;
    cmd_result = hackrf_set_freq(device, freq_hz);
    if (cmd_result != HACKRF_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    std::cout << "[*] hackrf frequency set" << std::endl;
    return true;
}

bool device_hackrf::set_sample_rate(double sample_rate) {
    device_hackrf::sample_rate = sample_rate;
    cmd_result = hackrf_set_sample_rate(device, sample_rate);
    if (cmd_result != HACKRF_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    std::cout << "[*] hackrf sample rate set" << std::endl;

    return true;
}

bool device_hackrf::rx_frequency(int seconds) {
    cmd_result = hackrf_start_rx(device, device_hackrf::rx_callback, nullptr);
    if (cmd_result != HACKRF_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    std::cout << "[*] hackrf rx started" << std::endl;

    int counter = 0;
    while ((hackrf_is_streaming(device) == HACKRF_TRUE) && counter < seconds) {
        // Sleep(1000);
        counter++;
    }

    std::cout << "[*] hackrf rx stopping" << std::endl;

    cmd_result = hackrf_stop_rx(device);
    if (cmd_result != HACKRF_SUCCESS)
    {
        return EXIT_FAILURE;
    }

    std::cout << "[*] hackrf captured successfully" << std::endl;
    return true;
}

int device_hackrf::rx_callback(hackrf_transfer* transfer) {
    if (fp != nullptr) {
        fwrite(transfer->device, transfer->valid_length, 1, fp);
    }
    return 0;
}