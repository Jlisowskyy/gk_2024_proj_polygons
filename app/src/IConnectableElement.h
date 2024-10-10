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

    void fullConnectionDelete() {
        qDebug() << "delete1";

        /* Start removal from RIGHT direction, when we found a cycle another direction is blocked */
        if (m_connectedElements[LEFT] != nullptr) {
            qDebug() << "WTF";
        }

        if (m_connectedElements[RIGHT] != nullptr) {
            m_connectedElements[RIGHT]->fullConnectionDelete(this, RIGHT);

            delete m_connectedElements[RIGHT];
            m_connectedElements[RIGHT] = nullptr;
        }

        if (m_connectedElements[LEFT] != nullptr) {
            m_connectedElements[LEFT]->fullConnectionDelete(this, LEFT);

            delete m_connectedElements[LEFT];
            m_connectedElements[LEFT] = nullptr;
        }
    }

    void fullConnectionDelete(void *startingElement, size_t direction) {
        qDebug() << "delete2";

        if (reinterpret_cast<void *>(this) == startingElement) {

            /* we found a cycle prevent removal from another direction */
            m_connectedElements[direction ^ 1] = nullptr;
            return;
        }

        if (m_connectedElements[direction] != nullptr) {
            m_connectedElements[direction]->fullConnectionDelete(startingElement, direction);
            delete m_connectedElements[direction];
        }
    }

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    std::array<T *, MAX_CONNECTIONS> m_connectedElements;
};

#endif //CONNECTABLEELEMENT_H
