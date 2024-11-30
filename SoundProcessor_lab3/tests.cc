#include "Exceptions.h"
#include "WavFile.h"
#include "Converter.h"
#include "ParseConfig.h"
#include "ParseConsole.h"
#include <gtest/gtest.h>
#include <fstream>


TEST(WAVFileTests, ReadValidFileFunkorama)
{
    WavFile wav; 
    ASSERT_NO_THROW(wav.read("C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\SoundProcessor_lab3\\build\\Debug\\funkorama.wav"));
    EXPECT_GT(wav.getSamples().size(), 0);
}

TEST(WAVFileTests, WriteValidFile)
{
    WavFile wav;
    ASSERT_NO_THROW(wav.read("C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\SoundProcessor_lab3\\build\\Debug\\funkorama.wav"));
    WavFile output;
    output.getSamples() = wav.getSamples();
    EXPECT_NO_THROW(output.write("C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\SoundProcessor_lab3\\build\\Debug\\output.wav"));
    EXPECT_GT(output.getSamples().size(), 0);
}


TEST(WAVFileTests, AccessSampleRateFunkorama)
{
    WavFile wav;
    ASSERT_NO_THROW(wav.read("C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\SoundProcessor_lab3\\build\\Debug\\funkorama.wav"));
    EXPECT_EQ(wav.getSampleRate(), 44100);
}

TEST(ConverterTest, ApplyMuteFromFile) {
   
    WavFile inputWav;
    ASSERT_TRUE(inputWav.read("C:\\Users\\user\\source\\repos\\NSU_LEARNING_CPP\\SoundProcessor_lab3\\build\\Debug\\funkorama.wav"));  

    std::vector<int16_t> inputSamples = inputWav.getSamples();

    
    MuteConverter muteConverter(0.5, 1.0);

    
    std::vector<int16_t> output = muteConverter.process(inputSamples);

    
    for (int i = 22050; i < 44100; ++i) {
        EXPECT_EQ(output[i], 0);  // Эти сэмплы должны быть заменены на 0
    }
}


TEST(ConverterTest, ApplyMixFromFile) {
   
    std::vector<int16_t> inputSamples1 = { 0, 1, 2 };
    std::vector<int16_t> inputSamples2 = { 300, 400 , 500 };

    size_t size1 = inputSamples1.size();
    size_t size2 = inputSamples2.size();

    // Используем более короткий файл для корректной работы
    size_t minSize = std::min(size1, size2);

    // Создаем MixConverter с дополнительным потоком и начальной позицией 0
    MixConverter mixConverter(inputSamples2, 0);

    // Применяем конвертер
    std::vector<int16_t> output = mixConverter.process(inputSamples1);

    // Перебираем минимальную длину для проверки
    for (size_t i = 0; i < minSize; ++i) {
        EXPECT_EQ(output[i], inputSamples1[i] + inputSamples2[i]);
    }
}

