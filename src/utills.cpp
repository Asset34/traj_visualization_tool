#include "utills.hpp"

PTraj *Utills::readTrajData(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "Cannot find " << file.fileName();
    }

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);

        /* Load tracjectory data from file */
        QString line;
        QStringList values;
        PTraj *ptraj = new PTraj;
        while (!stream.atEnd()) {
            line = stream.readLine();
            values = line.split(',');

            ptraj->add(values.at(0).toFloat(),
                       values.at(1).toFloat(),
                       values.at(2).toFloat());
        }

        file.close();

        /* Stream debug info */
        if (stream.status() == QTextStream::Ok) {
            qDebug() << "The trajectory was successfully loaded from " << file.fileName();

            return ptraj;
        }
        else {
            qDebug() << "The tracjection was not loaded from" << file.fileName();
        }
    }
    else {
        qDebug() << "Cannot load trajectory from " << file.fileName();
    }

    return nullptr;
}

int Utills::numDecimals(double value)
{
    QString strValue = QString::number(value);
    int dotPos = strValue.indexOf('.');

    if (dotPos == -1) {
        return 0;
    }
    else {
        return strValue.count() - dotPos - 1;
    }
}
