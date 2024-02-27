#include <iostream>
using namespace std;

class frazioni {
		int numeratore, denominatore;
	public:
		frazioni() {
			numeratore = 0, denominatore = 1;
		}

		frazioni(int n, int d) {
			set(n, d);
		}

		bool check() {
			return (denominatore == 0);
		}

		void set(int n, int d) {
			numeratore = n;
			denominatore = d;
			if (check())
				denominatore = 1;
		}

		void inserisci() {
			cout << "inserisci la frazione (numeratore/denominatore) -->";
			scanf("%d%*c%d", &numeratore, &denominatore);
			if (check())
				denominatore = 1;
		}

		friend istream & operator>>(istream &in,  frazioni &f) {
			in >> f.numeratore;
			in >> f.denominatore;
			in.get();
			return in;
		}

		friend ostream & operator<<(ostream &out, frazioni &f) {
			out << f.numeratore << "/" << f.denominatore;
			return out;
		}



		void setNumeratore(int n) {
			set(n, denominatore);
		}
		void setDenominatore(int d) {
			if (d) denominatore = d;
		}

		int getNumeratore() {
			return numeratore;
		}
		int getDenominatore() {
			return denominatore;
		}

		void print() {
			cout << numeratore << "/" << denominatore << endl;
		}

		int mcd(int n, int d) {
			if (n == 1 || d == 1)
				return 1;
			if (n == d)
				return n;
			if (n < d)
				return mcd(n, d - n);
			else
				return mcd(n - d, d);
		}

		frazioni minimiTermini() {
			int num = mcd(numeratore, denominatore);
			numeratore /= num, denominatore /= num;
			return *this;
		}

		double decimale() {
			return (double) numeratore / denominatore;
		}

		frazioni operator*(frazioni f2) {
			frazioni dep = *this;
			moltiplicazione(f2.numeratore);
			dep.denominatore *= f2.denominatore;
			return dep.minimiTermini();
		}
		
		frazioni operator*(int n) {
			frazioni dep = *this;
			dep.numeratore *= n;
			return dep.minimiTermini();
		}

		frazioni moltiplicazione(int n) {
			frazioni dep = *this;
			dep.numeratore *= n;
			return dep.minimiTermini();
		}

		frazioni operator/(frazioni f2) {
			frazioni dep = *this;
			frazioni div;
			dep.denominatore = f2.numeratore;
			dep.numeratore = f2.denominatore;
			div = *this * f2;
			return div.minimiTermini();
		}

		frazioni operator+(frazioni f2) {
			int c = 2;
			frazioni dep = *this;
			frazioni tempf1 = *this;
			frazioni tempf2 = f2;
			frazioni fin;
			
			if (dep.denominatore != f2.denominatore) {
				if (dep.denominatore > f2.denominatore) {
					while (dep.denominatore % f2.denominatore != 0) {
						dep.denominatore *= c;
						c++;
					}
					dep.numeratore = (dep.denominatore / tempf1.denominatore) * tempf1.numeratore;
					f2.numeratore = (dep.denominatore / tempf2.denominatore) * tempf2.numeratore;
					fin.numeratore = dep.numeratore + f2.numeratore;
					fin.denominatore = dep.denominatore;
				} else if	(dep.denominatore < f2.denominatore) {
					while (f2.denominatore % dep.denominatore != 0) {
						f2.denominatore *= c;
						c++;
					}
					dep.numeratore = (f2.denominatore / tempf1.denominatore) * tempf1.numeratore;
					f2.numeratore = (f2.denominatore / tempf2.denominatore) * tempf2.numeratore;
					fin.numeratore = dep.numeratore + f2.numeratore;
					fin.denominatore = f2.denominatore;
				}
			} else {
				fin.numeratore = dep.numeratore + f2.numeratore;
			}
			return fin.minimiTermini();
		}

		frazioni operator-(frazioni f2) {
			int c = 2;
			frazioni dep = *this;
			frazioni tempf1 = *this;
			frazioni tempf2 = f2;
			frazioni fin;

			if (dep.denominatore != f2.denominatore) {
				if (dep.denominatore > f2.denominatore) {
					while (dep.denominatore % f2.denominatore != 0) {
						dep.denominatore *= c;
						c++;
					}
					dep.numeratore = (dep.denominatore / tempf1.denominatore) * tempf1.numeratore;
					f2.numeratore = (dep.denominatore / tempf2.denominatore) * tempf2.numeratore;
					fin.numeratore = dep.numeratore - f2.numeratore;
					fin.denominatore = dep.denominatore;
				} else if	(dep.denominatore < f2.denominatore) {
					while (f2.denominatore % dep.denominatore != 0) {
						f2.denominatore *= c;
						c++;
					}
					dep.numeratore = (f2.denominatore / tempf1.denominatore) * tempf1.numeratore;
					f2.numeratore = (f2.denominatore / tempf2.denominatore) * tempf2.numeratore;
					fin.numeratore = dep.numeratore - f2.numeratore;
					fin.denominatore = f2.denominatore;
				}
			} else {
				fin.numeratore = dep.numeratore - f2.numeratore;
			}
			return fin.minimiTermini();
		}
};

void menu() {
	int scelta;
	frazioni f1, f2, fs, fdiv, fsott, fmol;
	double decimale = 0;
	do {
		cout << "[1] Inserisci una frazione" << endl;
		cout << "[2] Inserisci la seconda frazione" << endl;
		cout << "[3] Somma di frazioni" << endl;
		cout << "[4] Sottrazione di frazioni" << endl;
		cout << "[5] Moltiplicazione di frazioni" << endl;
		cout << "[6] Divisione di frazioni" << endl;
		cout << "[7] Stampa frazione 1 decimale" << endl;
		cout << "[8] Stampa frazione 2 decimale" << endl;
		cout << "[0] Esci" << endl;

		cout << "Opzione n.";
		cin >> scelta;

		switch (scelta) {
			case 1:
				f1.inserisci();
				break;
			case 2:
				f2.inserisci();
				break;
			case 3:
				f1.print();
				cout << " + " << endl;
				f2.print();
				fs = f1 + f2;
				cout << endl << "Risultato: ";
				fs.print();
				cout << endl << endl << "Risultato in decimale: ";
				decimale = fs.decimale();
				cout << decimale << endl;
				break;
			case 4:
				f1.print();
				cout << " - " << endl;
				f2.print();
				fsott = f1 - f2;
				cout << endl << "Risultato: ";
				fsott.print();
				cout << endl << endl << "Risultato in decimale: ";
				decimale = fsott.decimale();
				cout << decimale << endl;
				break;
			case 5:
				f1.print();
				cout << " * " << endl;
				f2.print();
				fmol = f1 * f2;
				cout << endl << "Risultato: ";
				fmol.print();
				cout << endl << endl << "Risultato in decimale: ";
				decimale = fmol.decimale();
				cout << decimale << endl;
				break;
			case 6:
				f1.print();
				cout << " / " << endl;
				f2.print();
				fdiv = f1 / f2;
				cout << endl << "Risultato: ";
				fdiv.print();
				cout << endl << endl << "Risultato in decimale: ";
				decimale = fdiv.decimale();
				cout << decimale << endl;
				break;
			case 7:
				f1.print();
				cout << " in decimale: ";
				f1.decimale();
			case 8:
				f2.print();
				cout << " in decimale: ";
				f2.decimale();
			case 0:
				exit(0);
				break;
			default:
				cout << "Opzione non valida. Inserisci nuovamente." << endl;
				break;
		}
	} while (scelta != 0);

}

int main() {

	menu();
	return 0;
}
