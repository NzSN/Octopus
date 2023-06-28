
#ifndef MESSAGE_H
#define MESSAGE_H

#include <concepts>
#include <string>
#include "Base/utility.hh"

namespace Octopus {
namespace Message {

class MessageBase {
public:
    std::string serialize();
};

} // Message
} // Octopus


#endif /* MESSAGE_H */
