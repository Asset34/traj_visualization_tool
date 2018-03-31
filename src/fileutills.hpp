#ifndef FILEUTILLS_HPP
#define FILEUTILLS_HPP

#include <QDebug>

#include "ptraj.hpp"

namespace FileUtills {

PMetaTraj readMetaTrajData(const QString &path);
PTraj readTrajData(const PMetaTraj &meta);

} // FileUtills


#endif // FILEUTILLS_HPP
