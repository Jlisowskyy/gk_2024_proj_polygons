//
// Created by Jlisowskyy on 10/10/24.
//

#ifndef CONNECTABLEELEMENT_H
#define CONNECTABLEELEMENT_H

/* internal includes */
#include "../Constants.h"

/* external includes */
#include <array>
#include <QDebug>

template<typename T>
class IConnectableElement {
    // ------------------------------
    // Class creation
    // ------------------------------
public:
    explicit IConnectableElement(void *parent) : m_parent(parent), m_connectedElements{nullptr, nullptr} {
    }

    virtual ~IConnectableElement() = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] size_t getConnectionIndex(T *const element) const {
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

    [[nodiscard]] T *getConnectedElement(const size_t direction) const {
        return m_connectedElements[direction];
    }

    void setConnectedElement(const size_t direction, T *element) {
        m_connectedElements[direction] = element;
    }

    [[nodiscard]] void *getLastConnectedElement(const size_t direction) {
        if (getConnectedElement(direction) == nullptr) {
            return m_parent;
        }

        return m_connectedElements[direction]->getLastConnectedElement(direction);
    }

    // ------------------------------
    // Class fields
    // ------------------------------
protected:
    void *m_parent{};
    std::array<T *, MAX_CONNECTIONS> m_connectedElements{};
};

#endif //CONNECTABLEELEMENT_H
