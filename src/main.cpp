#include <iostream>
#include <chrono>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

#include "cross_methods.cpp"

typedef std::chrono::steady_clock timer;
typedef std::chrono::duration<double, std::micro> timespan;
typedef std::chrono::time_point<timer> time_point;


int main(int argc, char** argv)
{
  const char sorted_symbols[257] = "   ``...---\'\'\':::__,,,^^^===;;>>><<<+++!!!rrccc***///zzz??sssLLLTTTvv)))JJJ777(((||FFFiii{{{CCC}}fffIII33311tttllluuu[[[nneeeoooZZZ55YYYxxxjjjyyyaa]]]222EEESSwwwqqqkkkPPP66hhh999ddd444VVpppOOOGGGbbUUUAAAKKKXXXHHmmm888RRRDDD##$$$BBBggg00MMMNNNWWWQQQ%%&&&@@@";

  if(argc < 2) { std::cout << "Video file not given"; return 1; }

  cv::VideoCapture Video(argv[1]);
  cv::Mat frame, temp_frame, out_frame;
  time_point time_start, time_end;

  int frametime = 1000000.0 / Video.get(cv::CAP_PROP_FPS);
  double font_as = 1.0f / 2.0f;
  std::string out_buffer;

  time_start = timer::now();
  while(Video.read(frame))
  {
    
    int w = 0, h = 0;
    get_terminal_size(w, h);
    
    double term_as = (double)w / h;
    double vid_as = (double)Video.get(cv::CAP_PROP_FRAME_WIDTH) / Video.get(cv::CAP_PROP_FRAME_HEIGHT);

    if(term_as * font_as > vid_as)
    { w = h * vid_as / font_as; }
    else
    { h = w / vid_as * font_as; }
    
    cv::resize(frame, temp_frame, cv::Size(w, h));
    cv::cvtColor(temp_frame, out_frame, cv::COLOR_RGB2GRAY);

    for(int row = 0; row < h; row++) 
    {
      if(row != 0)
        { std::cout << '\n'; }
      for(int col = 0; col < w; col++)
        { std::cout << sorted_symbols[(int)out_frame.at<uchar>(row, col)]; }
    }
    std::cout << "\033[H";

    time_end = timer::now();

    timespan timediff = (time_end - time_start);
    int towait = frametime - timediff.count();
    if(towait > 0)
    { wait_us(towait); }
    time_start = timer::now();
}
  
  Video.release();
  std::cout << "Unable to read next frame, exiting..." << std::endl;
  return 0;
}
