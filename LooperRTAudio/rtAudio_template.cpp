#include <iostream>
#include <unistd.h>
#include <thread>
#include "RtAudio.h"

// rtAudio variables
unsigned int bufferFrames, fs = 44100, offset = 0;
unsigned int channs;
RtAudio::StreamOptions options;
const unsigned int callbackReturnValue = 1;
int buffersize = 512;
unsigned int frameCounter = 0;
bool checkCount = false;
unsigned int nFrames = 0;
unsigned int bufferBytes;

// rtAudio callback function
int audioloop( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double /*streamTime*/, RtAudioStreamStatus status, void *data )
{
  unsigned int i;
  double samp;
  extern unsigned int channs;
  double *buffer = (double *) outputBuffer; // output buffer that we pass back to rtaudio

  for ( i=0; i<nBufferFrames; i++ )
  {
    // Get the sample from bowedstring


    //samp = !!!PLAATS JE SAMPLE HIER !!!

    // Voor stereo output, zet hier 2 verschillende samples:

    *buffer++ = samp; // get left output
    *buffer++ = samp; // get right output
  }

  frameCounter += nBufferFrames;
  if ( checkCount && ( frameCounter >= nFrames ) ) return callbackReturnValue;
  return 0;
}

// rtAudio setup
void realtime_audio()
{
  RtAudio dac;

  if ( dac.getDeviceCount() < 1 )
  {
    std::cout << "\nNo audio devices found!\n";
    exit( 1 );
  }

  channs = 2;

  double *data = (double *) calloc( channs, sizeof( double ) );

  // Let RtAudio print messages to stderr.
  dac.showWarnings( true );

  // Set our stream parameters
  bufferFrames = buffersize;
  RtAudio::StreamParameters oParams;
  oParams.deviceId = dac.getDefaultOutputDevice();
  oParams.nChannels = channs;
  oParams.firstChannel = offset;

  RtAudio::StreamParameters iParams;
  iParams.deviceId = dac.getDefaultInputDevice();
  iParams.nChannels = 1;
  iParams.firstChannel = offset;

  options.flags = RTAUDIO_HOG_DEVICE;
  options.flags = RTAUDIO_SCHEDULE_REALTIME;

  try
  {
    // Open the stream, passes the audio processing function
    dac.openStream( &oParams, &iParams, RTAUDIO_FLOAT64, fs, &bufferFrames, &audioloop, (void *)&bufferBytes, &options );
    dac.startStream();
  }
  catch ( RtAudioError& e )
  {
    e.printMessage();
    goto cleanup;
  }

  if ( checkCount )
  {
    while ( dac.isStreamRunning() == true ) usleep( 100 );
  }
  else
  {
    std::cout << "Stream latency = " << dac.getStreamLatency() << "\n" << std::endl;
  }

  while(true)
  {
    usleep(2000);
  }

cleanup:
  if ( dac.isStreamOpen() ) dac.closeStream();
  free( data );
}



int main()
{
  realtime_audio();
}
