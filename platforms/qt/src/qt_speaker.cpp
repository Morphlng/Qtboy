#include "qt_speaker.h"
#include "raw_audio.hpp"
#include <iostream>

#include <QDebug>

Qt_speaker::Qt_speaker(QObject *parent)
    : QObject {parent}
{
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16); // or 8 with UnSignedInt
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo dev = QAudioDeviceInfo::defaultOutputDevice();
    if (!dev.isFormatSupported(format)) {
        format = dev.nearestFormat(format);
    }

    m_audioOutput = new QAudioOutput(dev, format, this);
    qreal linearVolume = QAudio::convertVolume(90 / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    m_audioOutput->setVolume(linearVolume);

    qAudioDevice = m_audioOutput->start(); // using push mode
}

void Qt_speaker::queue_samples(const qtboy::Raw_audio &a)
{
    const char *buffer = (char *) a.data();
    qint64 bytesAvaliable = a.size();
    while (bytesAvaliable) {
        qint64 bytesWritten = qAudioDevice->write(buffer, bytesAvaliable);
        bytesAvaliable -= bytesWritten;
        buffer += bytesWritten;
    }
}

int Qt_speaker::samples_queued()
{
    return 0;
}

void Qt_speaker::clear_samples()
{

}
