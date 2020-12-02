#pragma once
#include "Stein.h"
#include <vector>

using namespace std;

#define V4_ROWS 6 //Anzahl der Reihen
#define V4_COLS 7 //Anzahl der Spalten

typedef unsigned int	size_t; //Definition von size_t (gucke vcruntime.h)

namespace V4
{
	static const size_t ROWS = V4_ROWS; //Anzahl der Reihen von VierGewinnt
	static const size_t COLS = V4_COLS; //Anzahl der Spalten von VierGewinnt

	class VierGewinnt
	{
	private:
		Stein gameField[ROWS][COLS];				//Zweidimensionales Array zur Darstellung des Spielfeldes
		SteinOwner gewinner;						//Speichert den Gewinner, Init = NONE
		std::vector<const Stein*>* gewinnerSteine;	//Seichert die GEwinner-Steine als Objekt
		SteinOwner currentPlayer;					//Speichert den Spieler, welcher den nächsten Zug vollziehen darf
		size_t remainingSteine;						//Speichert, wieviele Steine frei sind

	public:
		//Default Constructor
		VierGewinnt(SteinOwner startingPlayer = SteinOwner::RED);

		//Default Deconstructor
		virtual ~VierGewinnt();

		//Setzt den Stein in eine Spezifische Spalte.
		//In der Methode werden currentPlayer und ggf. der Gewinner ausgewertet.
		//Die Funktion gibt folgende Werte zurück:
		// 2:	Spiel ist unentschieden
		// 1:	Es hat jemand gewonnen (gucke getGewinner())
		// 0:	Zug erfolgreich, der nächste Spieler kann ein Stein setzen
		//-1:	Die Spalten entspricht nicht den zu wählenden Grenzen (Grenze: [0,6])
		//-2:	Spalte ist voll, wähle eine andere Spalte
		//-3:	Unbekannter Fehler
		uint32_t putStein(const uint8_t col, const SteinOwner owner);

		//Setzt den Owner des Steins an der Position (row, col)
		void setStein(const uint8_t row, const uint8_t col, const SteinOwner owner);

		//Gibt einen Vector mit allen Steinen wieder, die zum Gewinnen führten
		vector<const Stein*>* winningSteine(const uint8_t row, const uint8_t col) const;

		//Gibt einen Vector mit allen Steinen wieder, die zum Gewinnen führten
		vector<const Stein*>* winningSteine(const Stein* toTest) const;

		//Gibt den Stein wieder, welcher sich an der Position (row, col) befindet.
		//Sollten sich row oder col außerhalb der Grenzen befinden, so wird ein nullptr zurückgegeben
		Stein* getStein(const uint8_t row, const uint8_t col);

		//const-Variante von getStein(...)
		//Für eine nähere Beschreibung: siehe getStein(const uint8_t row, const uint8_t col);
		const Stein* getStein(const uint8_t row, const uint8_t col) const;

		/*
		GETTER UND SETTER
		*/

		Stein* getGameField()
		{
			return *gameField;
		}

		const Stein* getGameField() const
		{
			return *gameField;
		}

		SteinOwner getGewinner() {
			return gewinner;
		}

		const SteinOwner getGewinner() const {
			return gewinner;
		}

		SteinOwner getCurrentPlayer() {
			return currentPlayer;
		}

		const SteinOwner getCurrentPlayer() const {
			return currentPlayer;
		}

		void setCurrentPlayer(SteinOwner player) {
			this->currentPlayer = player;
		}

		std::vector<const Stein*>* getWinningSteine() {
			return gewinnerSteine;
		}

		const std::vector<const Stein*>* getWinningSteine() const {
			return gewinnerSteine;
		}

	private:
		//Gibt TRUE zurück, wenn sich vier Steine der gleichen Farbe in einer Reihe (drow, dcol UND -drow, -dcol) befinden
		//Wird TRUE zurückgegeben, so werden in dem Vector steine, die Steine, welche sich ín der Reihe befinden, hinzugefügt
		const bool fourInOneDirection(const Stein* stein, int drow, int dcol, vector<const Stein*> &steine) const;

		//Initialisiert das Spielfeld mit den Standartwerten
		void resetGameField();
	};
} // namespace V4