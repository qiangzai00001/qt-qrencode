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
#ifndef QRCODEITEM_H
#define QRCODEITEM_H

#include <QQuickPaintedItem>

class QRCodeItem : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(int version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(ErrorLevel level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(EncodeMode hint READ hint WRITE setHint NOTIFY hintChanged)
    Q_PROPERTY(int padding READ padding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    enum EncodeMode {
        ENCODE_MODE_NULL = -1,
        ENCODE_MODE_NUMERIC  = 0,
        ENCODE_MODE_ALNUM,
        ENCODE_MODE_8BIT,
        ENCODE_MODE_KANJI
    };
    Q_ENUMS(EncodeMode)

    enum ErrorLevel {
        ERROR_LEVEL_LOW = 0,
        ERROR_LEVEL_MEDIUM,
        ERROR_LEVEL_QUALITY,
        ERROR_LEVEL_HIGH
    };
    Q_ENUMS(ErrorLevel)

    explicit QRCodeItem(QQuickItem *parent = 0);
            ~QRCodeItem();

    int version() const;
    Q_INVOKABLE void setVersion(int version);

    ErrorLevel level() const;
    Q_INVOKABLE void setLevel(ErrorLevel level);

    EncodeMode hint() const;
    Q_INVOKABLE void setHint(EncodeMode hint);

    int padding() const;
    Q_INVOKABLE void setPadding(int padding);

    QColor color() const;
    Q_INVOKABLE void setColor(const QColor &color);

    QString text() const;
    Q_INVOKABLE void setText(const QString &text);

Q_SIGNALS:
    void versionChanged();
    void levelChanged();
    void hintChanged();
    void textChanged();
    void paddingChanged();
    void colorChanged();

protected:
    void draw(QPainter *painter, int w, int h);
    void paint(QPainter *painter);

private:
    class QRCodeItemPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QRCodeItem)
};

#endif // QRCODEITEM_H
