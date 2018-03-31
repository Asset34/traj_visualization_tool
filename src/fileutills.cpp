#include "fileutills.hpp"

PMetaTraj FileUtills::readMetaTrajData(const QString &path)
{
    // TODO
}

PTraj FileUtills::readTrajData(const PMetaTraj &meta)
{
    QFile file(meta.dataPath);

    if (!file.exists()) {
        qDebug() << "Cannot find " << file.fileName();
    }

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);

        /* Load tracjectory data from file */
        QString line;
        QStringList values;
        State state;
        PTraj traj(meta.timeStep);
        while (!stream.atEnd()) {
            line = stream.readLine();
            values = line.split(',');

            state = {values.at(0).toDouble(),
                     values.at(1).toDouble(),
                     values.at(2).toDouble()};

            traj.add(state);
        }

        /* Stream debug info */
        if (stream.status() == QTextStream::Ok) {
            qDebug() << "The trajectory was successfully loaded from " << file.fileName();
        }
        else {
            qDebug() << "The tracjection was not loaded from" << file.fileName();
        }

        file.close();
    }
    else {
        qDebug() << "Cannot load trajectory from " << file.fileName();
    }
}
