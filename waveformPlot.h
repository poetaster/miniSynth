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

#ifndef WAVEFORMPLOT_H
#define WAVEFORMPLOT_H

#include <QWidget>
#include <QPixmap>
#include <QPen>
#include <QStylePainter>

#include "linearSynthesis.h"

class WaveformPlot : public QWidget {
    Q_OBJECT
public:
    WaveformPlot(QWidget *parent = 0);
    ~WaveformPlot();

public slots:
    void setMode(int _mode);
    void setTimbre(QVector<int> &amplitudes, QVector<int> &phases);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    void refreshPixmap();
    QPixmap pixmap;

    LinearSynthesis *waveForm;
    int mode;
    int border;
};

#endif // WAVEFORMPLOT_H
