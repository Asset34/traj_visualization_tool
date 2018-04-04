#ifndef FILEUTILLS_HPP
#define FILEUTILLS_HPP

#include <QDebug>

#include "ptraj.hpp"

namespace FileUtills {

PTrajMeta readTrajMetaData(const QString &path);
PTraj readTrajData(const PTrajMeta &meta);

} // FileUtills


#endif // FILEUTILLS_HPP
