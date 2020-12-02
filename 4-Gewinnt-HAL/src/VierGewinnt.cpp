#include "VierGewinnt.h"
#include <cstddef>

namespace V4
{
    VierGewinnt::VierGewinnt(SteinOwner startingPlayer)
    {
        this->currentPlayer = startingPlayer;
        this->remainingSteine = ROWS * COLS;
        this->gewinner = SteinOwner::NONE;
        this->gewinnerSteine = nullptr;

        resetGameField();
    }

    VierGewinnt::~VierGewinnt()
    {
        if (this->gewinnerSteine != nullptr)
            delete gewinnerSteine;
    }

    void VierGewinnt::resetGameField()
    {
        for (int r = 0; r < ROWS; r++)
            for (int c = 0; c < COLS; c++)
                gameField[r][c] = Stein(SteinOwner::NONE, r, c);
    }

    Stein *VierGewinnt::getStein(const uint8_t row, const uint8_t col)
    {
        if (row >= V4::ROWS || col >= V4::COLS)
            return nullptr;

        return &gameField[row][col];
    }

    const Stein *VierGewinnt::getStein(const uint8_t row, const uint8_t col) const
    {
        if (row >= V4::ROWS || col >= V4::COLS)
            return nullptr;

        return &gameField[row][col];
    }

    uint32_t VierGewinnt::putStein(const uint8_t col, const SteinOwner owner)
    {
        if (col >= V4::COLS || col < 0)
            return -1;

        if (this->getStein(0, col)->owner != SteinOwner::NONE)
            return -2;

        // Search for floor below, from top to bottom
        for (uint8_t row = 0; row < V4::ROWS; row++)
        {
            const Stein *steinBelow = this->getStein(row + 1, col);
            if (steinBelow == NULL || steinBelow->owner != SteinOwner::NONE)
            {
                this->setStein(row, col, owner);
                this->remainingSteine--;

                //change turn
                this->setCurrentPlayer(currentPlayer == SteinOwner::RED ? SteinOwner::YELLOW : SteinOwner::RED);

                std::vector<const Stein *> *steine = winningSteine(row, col);

                if (steine != nullptr)
                {
                    this->gewinner = owner;
                    this->gewinnerSteine = steine;
                    return 1;
                }
                if (remainingSteine == 0)
                {
                    this->gewinner = SteinOwner::NONE;
                    return 2;
                }

                return 0;
            }
        }

        return -3;
    }

    void VierGewinnt::setStein(const uint8_t row, const uint8_t col, const SteinOwner owner)
    {
        if (row >= V4::ROWS)
            return;
        if (col >= V4::COLS)
            return;

        this->gameField[row][col].owner = owner;
    }

    vector<const Stein *> *VierGewinnt::winningSteine(const uint8_t row, const uint8_t col) const
    {
        return winningSteine(this->getStein(row, col));
    }

    vector<const Stein *> *VierGewinnt::winningSteine(const Stein *stein) const
    {
        bool winnerExists = false;
        vector<const Stein *> *winningSteine = new vector<const Stein *>();

        vector<const Stein *> dummy;
        if (fourInOneDirection(stein, 1, 1, dummy))
        {
            winnerExists = true;
            for (const Stein *a : dummy)
                winningSteine->push_back(a);
        }

        dummy.clear();

        if (fourInOneDirection(stein, 1, 0, dummy))
        {
            winnerExists = true;
            for (const Stein *a : dummy)
                winningSteine->push_back(a);
        }

        dummy.clear();

        if (fourInOneDirection(stein, 0, 1, dummy))
        {
            winnerExists = true;
            for (const Stein *a : dummy)
                winningSteine->push_back(a);
        }

        dummy.clear();

        if (fourInOneDirection(stein, 1, -1, dummy))
        {
            winnerExists = true;
            for (const Stein *a : dummy)
                winningSteine->push_back(a);
        }

        if (winnerExists)
        {
            winningSteine->push_back(stein);

            return winningSteine;
        }
        else
        {
            delete winningSteine;
            return nullptr;
        }
    }

    const bool VierGewinnt::fourInOneDirection(const Stein *stein, int drow, int dcol, vector<const Stein *> &steine) const
    {
        int currentCol = stein->col + dcol;
        int currentRow = stein->row + drow;
        const Stein *current = this->getStein(currentRow, currentCol);
        size_t num = 1;

        while (current != NULL && current->owner == stein->owner)
        {
            num++;
            currentCol += dcol;
            currentRow += drow;
            steine.push_back(current);
            current = this->getStein(currentRow, currentCol);
        }

        drow = -drow;
        dcol = -dcol;
        currentCol = stein->col + dcol;
        currentRow = stein->row + drow;
        current = this->getStein(currentRow, currentCol);

        while (current != NULL && current->owner == stein->owner)
        {
            num++;
            currentCol += dcol;
            currentRow += drow;
            steine.push_back(current);
            current = this->getStein(currentRow, currentCol);
        }

        return num >= 4;
    }
} // namespace V4