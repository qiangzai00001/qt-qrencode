/*
    Copyright (C) 2011-2016 Imogen Software Carsten Valdemar Munk

    Contact: Tom Swindell <t.swindell@rubyx.co.uk>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "qrcodeitem.h"

#include <math.h>
#include <qrencode.h>

#include <QPainter>

class QRCodeItemPrivate
{
public:
    QRCodeItemPrivate()
        : encoder(NULL),
          version(1),
          level(QRCodeItem::ERROR_LEVEL_MEDIUM),
          hint(QRCodeItem::ENCODE_MODE_8BIT),
          padding(0),
          color(Qt::black)
    { /* ... */ }

    QRcode *encoder;

    int version;
    QRCodeItem::ErrorLevel level;
    QRCodeItem::EncodeMode hint;
    int padding;
    QColor color;
    QString text;
};

QRCodeItem::QRCodeItem(QQuickItem *parent)
    : QQuickPaintedItem(parent), d_ptr(new QRCodeItemPrivate)
{
    this->setFlag(QQuickItem::ItemHasContents, true);
}

QRCodeItem::~QRCodeItem()
{
    Q_D(QRCodeItem);
    if(d->encoder) delete d->encoder;
    delete d_ptr;
}

int QRCodeItem::version() const
{
    Q_D(const QRCodeItem);
    return d->version;
}

void QRCodeItem::setVersion(int version)
{
    Q_D(QRCodeItem);
    if(d->version != version)
    {
        d->version = version;
        if(d->encoder) //TODO: do we really need to start fresh?
        {
            delete d->encoder;
            d->encoder = NULL;
        }

        this->update();
        emit this->versionChanged();
    }
}

QRCodeItem::ErrorLevel QRCodeItem::level() const
{
    Q_D(const QRCodeItem);
    return d->level;
}

void QRCodeItem::setLevel(ErrorLevel level)
{
    Q_D(QRCodeItem);
    if(d->level != level)
    {
        d->level = level;

        if(d->encoder)
        {
            delete d->encoder;
            d->encoder = NULL;
        }

        this->update();
        emit this->levelChanged();
    }
}


QRCodeItem::EncodeMode QRCodeItem::hint() const
{
    Q_D(const QRCodeItem);
    return d->hint;
}

void QRCodeItem::setHint(EncodeMode hint)
{
    Q_D(QRCodeItem);
    if(d->hint != hint)
    {
        d->hint = hint;

        if(d->encoder)
        {
            delete d->encoder;
            d->encoder = NULL;
        }

        this->update();
        emit this->hintChanged();
    }
}

int QRCodeItem::padding() const
{
    Q_D(const QRCodeItem);
    return d->padding;
}

void QRCodeItem::setPadding(int padding)
{
    Q_D(QRCodeItem);
    if(d->padding != padding)
    {
        d->padding = padding;

        this->update();
        emit this->paddingChanged();
    }
}
QColor QRCodeItem::color() const
{
    Q_D(const QRCodeItem);
    return d->color;
}

void QRCodeItem::setColor(const QColor &color)
{
    Q_D(QRCodeItem);
    if(d->color != color)
    {
        d->color = color;
        this->update();
        emit this->colorChanged();
    }
}

QString QRCodeItem::text() const
{
    Q_D(const QRCodeItem);
    return d->text;
}

void QRCodeItem::setText(const QString &text)
{
    Q_D(QRCodeItem);
    if(d->text != text)
    {
        d->text = text;

        if(d->encoder)
        {
            delete d->encoder;
            d->encoder = NULL;
        }

        this->update();
        emit this->textChanged();
    }
}

void QRCodeItem::draw(QPainter *painter, int w, int h)
{
    Q_D(QRCodeItem);
    // Check to see if we need to generate the QRCode.
    if(!d->encoder && !d->text.isNull())
    {
        d->encoder = QRcode_encodeString(d->text.toLatin1(),
                                         d->version,
                                         static_cast<QRecLevel>(d->level),
                                         static_cast<QRencodeMode>(d->hint),
                                         1);
    }

    // Draw background.
    //painter->setPen(QPen(d->background));
    //painter->fillRect(0, 0, w, h, d->background);

    // If we don't have an encoded code, then don't render foreground.
    if(!d->encoder) return;

    int s = (w > h ? h : w) - d->padding;
    int b = s / d->encoder->width; // Block size.

    s = b * d->encoder->width;

    // Offsets for placing image in centre.
    int x = (w - s) / 2;
    int y = (h - s) / 2;

    // Draw foreground
    painter->setPen(QPen(d->color));
    for(int i = 0; i < d->encoder->width * d->encoder->width; i++)
    {
        int c = i % d->encoder->width; // Current column index
        int r = i / d->encoder->width; // Current row index

        // If block is ON then fill in.
        if(d->encoder->data[i] & 0x01)
        {
            painter->fillRect(floor(x + b * c),
                              floor(y + b * r),
                              b, b,
                              d->color);
        }
    }
}

void QRCodeItem::paint(QPainter *painter)
{
    this->draw(painter, floor(this->boundingRect().width()), floor(this->boundingRect().height()));
}
