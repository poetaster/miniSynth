/* miniSynth - A Simple Software Synthesizer
   Copyright (C) 2015 Ville Räisänen <vsr at vsr.name>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OUTPUTQT_H
#define OUTPUTQT_H

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>

#include <QList>
#include <QMutableListIterator>

#include "linearSynthesis.h"
#include "ADSRenvelope.h"

class Wave {
public:
    enum {STATE_OFF, STATE_ATTACK, STATE_DECAY, STATE_RELEASE};
    unsigned char note, vel, state;
    qreal state_age;
};

class Generator : public QIODevice {
    Q_OBJECT
public:
    Generator(const QAudioFormat &_format, QObject *parent = 0);
    ~Generator();

    void start    ();
    void stop     ();
    void setState ();

    void addWave (unsigned char note, unsigned char vel);

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

    void generateData(qint64 len);
    qreal curtime;
public slots:
    void noteOn   (unsigned char chan, unsigned char note, unsigned char vel);
    void noteOff  (unsigned char chan, unsigned char note);
    void setMode  (int _mode);
    void setTimbre(QVector<int> &amplitudes, QVector<int> &phases);
    void setEnvelope(ADSREnvelope &env);
private:
    QAudioFormat format;
    QByteArray m_buffer;

    QList<Wave> waveList;
    LinearSynthesis *linSyn;
    ADSREnvelope env;
};

#endif // OUTPUTQT_H