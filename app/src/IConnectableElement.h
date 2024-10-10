//
// Created by Jlisowskyy on 10/10/24.
//

#ifndef CONNECTABLEELEMENT_H
#define CONNECTABLEELEMENT_H

/* internal includes */
#include "Constants.h"

/* external includes */
#include <array>

template<size_t N, typename T>
class IConnectableElement {
    // ------------------------------
    // Class creation
    // ------------------------------
    public:

    IConnectableElement(){}

    // ------------------------------
    // Class interaction
    // ------------------------------

    T* getConnectedElement(size_t index) const {
        return m_connectedElements[index];
    }

    void setConnectedElement(T* element, size_t index) {
        m_connectedElements[index] = element;
    }

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    std::array<T*, N> m_connectedElements{};
};

#endif //CONNECTABLEELEMENT_H
