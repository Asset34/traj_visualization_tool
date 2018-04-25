#ifndef UTILLS_HPP
#define UTILLS_HPP

#include <QFile>
#include <QStringList>

#include <QDebug>

#include "Opengl/ptraj.hpp"

namespace Utills {

/* Ptraj utills */
PTraj *readTrajData(const QString &path);

} // Utills

#endif // UTILLS_HPP
