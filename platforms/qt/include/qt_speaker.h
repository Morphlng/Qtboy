#ifndef QT_SPEAKER_H
#define QT_SPEAKER_H

#include "raw_audio.hpp"
#include "speaker.hpp"

#include <QAudioOutput>
#include <QObject>

class Qt_speaker : public QObject, public qtboy::Speaker
{
    Q_OBJECT

public:
    explicit Qt_speaker(QObject *parent = nullptr);
    virtual ~Qt_speaker() = default;

    void queue_samples(const qtboy::Raw_audio &a) override;
    int samples_queued() override;
    void clear_samples() override;

private:
    int buffer_size_{};
    QAudioOutput *m_audioOutput{nullptr};
    QIODevice *qAudioDevice{nullptr};
};

#endif // QT_SPEAKER_


