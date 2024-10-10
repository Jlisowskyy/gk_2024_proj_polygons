//
// Created by Jlisowskyy on 10/10/24.
//

#ifndef CONNECTABLEELEMENT_H
#define CONNECTABLEELEMENT_H

/* internal includes */
#include "Constants.h"

/* external includes */
#include <array>
#include <QDebug>

template<typename T>
class IConnectableElement {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    IConnectableElement() : m_connectedElements{nullptr, nullptr} {}

    virtual ~IConnectableElement() = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] size_t getConnectionIndex(T *element) const {
        if (element == nullptr) {
            return MAX_CONNECTIONS;
        }

        for (size_t idx = 0; idx < MAX_CONNECTIONS; ++idx) {
            if (m_connectedElements[idx] == element) {
                return idx;
            }
        }

        return MAX_CONNECTIONS;
    }

    [[nodiscard]] T *getConnectedElement(size_t index) const {
        return m_connectedElements[index];
    }

    void setConnectedElement(size_t index, T *element) {
        m_connectedElements[index] = element;
    }

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    std::array<T *, MAX_CONNECTIONS> m_connectedElements;
};

#endif //CONNECTABLEELEMENT_H
