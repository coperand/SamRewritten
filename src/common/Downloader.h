#pragma once
#include <unistd.h>
#include <string>
#include "../../steam/steamtypes.h"

/**
 * This class is used to download files from the internet
 * It follows a single singleton pattern and is meant to be very basic.
 * 
 * Launching lots of simultaneous downloads causes DNS resolution to start
 * failing, so users of this class should limit to ~10 simultaneous downloads for now...
 */
class Downloader
{
public:
    /**
     * Singleton method to get the unique instance
     */
    static Downloader* get_instance();

    /**
     * Downloads a file synchronously. If the download fails, the program will exit.
     * If the local_path already exists on the disk, the download will be skipped (as it if was successful)
     * Async downloads can be implemented by firing off a thread with this function.
     */
    static void download_file(const std::string& file_url, const std::string& local_path);

    /**
     * Delete these, as no one will need them with the singleton pattern
     */
    Downloader(Downloader const&)                 = delete;
    void operator=(Downloader const&)             = delete;

private:
    Downloader() {};
    ~Downloader() {};
};
