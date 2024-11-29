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


TEST(ConverterTest, ApplyEcho) {
    // Входные данные: 5 сэмплов
    std::vector<int16_t> input(44105, 100);

    // Создаем конвертер с задержкой 1 сэмпл и затуханием 0.5 (50%)
    EchoConverter echoConverter(1, 50.0f);  // Задержка 1 сэмпл и затухание 50%

    // Применяем конвертер
    std::vector<int16_t> output = echoConverter.process(input);

    // Проверяем, что сэмплы после эха правильно обработаны
    EXPECT_EQ(output[44100], 100);  // Первый сэмпл остается без изменений
    EXPECT_EQ(output[44101], 250);  // Второй сэмпл: 200 + (100 * 0.5)
    EXPECT_EQ(output[44102], 350);  // Третий сэмпл: 300 + (200 * 0.5)
    EXPECT_EQ(output[44103], 450);  // Четвертый сэмпл: 400 + (300 * 0.5)
    EXPECT_EQ(output[44104], 550);  // Пятый сэмпл: 500 + (400 * 0.5)
}


