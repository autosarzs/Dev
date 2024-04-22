#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dio.h"

int main()
{
  // Test case 1: Test with valid channel ID
  {
    Dio_ChannelType channelId = 1; // Change this to a valid channel ID
    Dio_LevelType result = Dio_ReadChannel(channelId);
    printf("Test case 1 result: %d\n", result);
    // Add assertions to verify the result
  }

  // Test case 2: Test with invalid channel ID
  {
    Dio_ChannelType channelId = -1; // Change this to an invalid channel ID
    Dio_LevelType result = Dio_ReadChannel(channelId);
    printf("Test case 2 result: %d\n", result);
    // Add assertions to verify the result
  }

  return 0;
}
