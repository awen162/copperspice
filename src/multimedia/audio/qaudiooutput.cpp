/***********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2012-2020 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#include <qaudio.h>
#include <qaudiodeviceinfo.h>
#include <qaudiosystem.h>
#include <qaudiooutput.h>

#include <qaudiodevicefactory_p.h>



QAudioOutput::QAudioOutput(const QAudioFormat &format, QObject *parent):
   QObject(parent)
{
   m_audioOutput = QAudioDeviceFactory::createDefaultOutputDevice(format);

   connect(m_audioOutput, &QAbstractAudioOutput::notify,       this, &QAudioOutput::notify);
   connect(m_audioOutput, &QAbstractAudioOutput::stateChanged, this, &QAudioOutput::stateChanged);
}

QAudioOutput::QAudioOutput(const QAudioDeviceInfo &audioDevice, const QAudioFormat &format, QObject *parent):
   QObject(parent)
{
   m_audioOutput = QAudioDeviceFactory::createOutputDevice(audioDevice, format);
   connect(m_audioOutput, &QAbstractAudioOutput::notify,       this, &QAudioOutput::notify);
   connect(m_audioOutput, &QAbstractAudioOutput::stateChanged, this, &QAudioOutput::stateChanged);
}

QAudioOutput::~QAudioOutput()
{
   delete m_audioOutput;
}

QAudioFormat QAudioOutput::format() const
{
   return m_audioOutput->format();
}

void QAudioOutput::start(QIODevice *device)
{
   m_audioOutput->start(device);
}

/*!
    Returns a pointer to the QIODevice being used to handle the data
    transfer. This QIODevice can be used to write() audio data directly.

    If able to access the systems audio device the state() is set to
    QAudio::IdleState, error() is set to QAudio::NoError
    and the stateChanged() signal is emitted.

    If a problem occurs during this process the error() is set to QAudio::OpenError,
    state() is set to QAudio::StoppedState and stateChanged() signal is emitted.

    In either case, the stateChanged() signal may be emitted either synchronously
    during execution of the start() function or asynchronously after start() has
    returned to the caller.

    \sa QIODevice
*/

QIODevice *QAudioOutput::start()
{
   return m_audioOutput->start();
}

/*!
    Stops the audio output, detaching from the system resource.

    Sets error() to QAudio::NoError, state() to QAudio::StoppedState and
    emit stateChanged() signal.
*/

void QAudioOutput::stop()
{
   m_audioOutput->stop();
}

/*!
    Drops all audio data in the buffers, resets buffers to zero.
*/

void QAudioOutput::reset()
{
   m_audioOutput->reset();
}

/*!
    Stops processing audio data, preserving buffered audio data.

    Sets error() to QAudio::NoError, state() to QAudio::SuspendedState and
    emit stateChanged() signal.
*/

void QAudioOutput::suspend()
{
   m_audioOutput->suspend();
}

/*!
    Resumes processing audio data after a suspend().

    Sets error() to QAudio::NoError.
    Sets state() to QAudio::ActiveState if you previously called start(QIODevice*).
    Sets state() to QAudio::IdleState if you previously called start().
    emits stateChanged() signal.

    Note: signal will always be emitted during execution of the resume() function.
*/

void QAudioOutput::resume()
{
   m_audioOutput->resume();
}

/*!
    Returns the free space available in bytes in the audio buffer.

    NOTE: returned value is only valid while in QAudio::ActiveState or QAudio::IdleState
    state, otherwise returns zero.
*/

int QAudioOutput::bytesFree() const
{
   return m_audioOutput->bytesFree();
}

/*!
    Returns the period size in bytes.

    Note: This is the recommended write size in bytes.
*/

int QAudioOutput::periodSize() const
{
   return m_audioOutput->periodSize();
}

/*!
    Sets the audio buffer size to \a value in bytes.

    Note: This function can be called anytime before start(), calls to this
    are ignored after start(). It should not be assumed that the buffer size
    set is the actual buffer size used, calling bufferSize() anytime after start()
    will return the actual buffer size being used.
*/

void QAudioOutput::setBufferSize(int value)
{
   m_audioOutput->setBufferSize(value);
}

/*!
    Returns the audio buffer size in bytes.

    If called before start(), returns platform default value.
    If called before start() but setBufferSize() was called prior, returns value set by setBufferSize().
    If called after start(), returns the actual buffer size being used. This may not be what was set previously
    by setBufferSize().

*/

int QAudioOutput::bufferSize() const
{
   return m_audioOutput->bufferSize();
}

/*!
    Sets the interval for notify() signal to be emitted.
    This is based on the \a ms of audio data processed
    not on actual real-time.
    The minimum resolution of the timer is platform specific and values
    should be checked with notifyInterval() to confirm actual value
    being used.
*/

void QAudioOutput::setNotifyInterval(int ms)
{
   m_audioOutput->setNotifyInterval(ms);
}

/*!
    Returns the notify interval in milliseconds.
*/

int QAudioOutput::notifyInterval() const
{
   return m_audioOutput->notifyInterval();
}

/*!
    Returns the amount of audio data processed by the class since start()
    was called in microseconds.

    Note: The amount of audio data played can be determined by subtracting
    the microseconds of audio data still in the systems audio buffer.

    \code
    qint64 bytesInBuffer = bufferSize() - bytesFree();
    qint64 usInBuffer = (qint64)(1000000) * bytesInBuffer / ( channels() * sampleSize() / 8 ) / frequency();
    qint64 usPlayed = processedUSecs() - usInBuffer;
    \endcode
*/

qint64 QAudioOutput::processedUSecs() const
{
   return m_audioOutput->processedUSecs();
}

/*!
    Returns the microseconds since start() was called, including time in Idle and
    Suspend states.
*/

qint64 QAudioOutput::elapsedUSecs() const
{
   return m_audioOutput->elapsedUSecs();
}

/*!
    Returns the error state.
*/

QAudio::Error QAudioOutput::error() const
{
   return m_audioOutput->error();
}

/*!
    Returns the state of audio processing.
*/

QAudio::State QAudioOutput::state() const
{
   return m_audioOutput->state();
}

void QAudioOutput::setVolume(qreal volume)
{
   qreal v = qBound(qreal(0.0), volume, qreal(1.0));
   m_audioOutput->setVolume(v);
}

qreal QAudioOutput::volume() const
{
   return m_audioOutput->volume();
}

QString QAudioOutput::category() const
{
   return m_audioOutput->category();
}

void QAudioOutput::setCategory(const QString &category)
{
   m_audioOutput->setCategory(category);
}
