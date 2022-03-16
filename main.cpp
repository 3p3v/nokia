//============================================================================
// Name        : threadstest.cpp
// Author      : ADAM
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"
using namespace std;

int width; //700
int heigth; //550
int width_w;
bool settings_loaded = false;

int quant;
int prior_quant;
std::vector<Process> processes;
std::vector<int> frames;
int length;
int num_o_frames;
bool frames_loaded = true;
bool processes_loaded = false;

void load_settings() {
	std::ifstream input("settings.txt");
	std::string line;

	if (input) {
		settings_loaded = true;

		std::getline(input, line);
		std::getline(input, line);

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) == false && isspace(line.at(i)) == false) {
				settings_loaded = false;
			} else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 1)
					settings_loaded = false;
			}

		}

		if (settings_loaded) {
			std::stringstream linestr(line);
			linestr >> width;
		}

		std::getline(input, line);

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) == false && isspace(line.at(i)) == false) {
				settings_loaded = false;
			} else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 1)
					settings_loaded = false;
			}
		}

		if (settings_loaded) {
			std::stringstream linestr(line);
			linestr >> heigth;
		}

		std::getline(input, line);
		std::getline(input, line);

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) == false && isspace(line.at(i)) == false) {
				settings_loaded = false;
			} else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 1)
					settings_loaded = false;
			}
		}

		if (settings_loaded) {
			std::stringstream linestr(line);
			linestr >> width_w;
		}
	}
}

void output(Fcfs *fcfs, Roundrobin *rr, PriorityNP *pnp) {
	if (fcfs->symended || rr->symended || pnp->symended) {
		std::time_t resultrn = time(NULL);
		tm *timern = localtime(&resultrn);

		std::string helper = "output\\scheduling_"
				+ std::to_string(1900 + timern->tm_year) + "-"
				+ std::to_string(1 + timern->tm_mon) + "-"
				+ std::to_string(timern->tm_mday) + "-"
				+ std::to_string(timern->tm_hour) + "-"
				+ std::to_string(timern->tm_min) + "-"
				+ std::to_string(timern->tm_sec) + ".txt";
		ofstream p_output(helper);

		p_output << "PID\tARRIVAL\tBURST_TIME\tPRIORITY\n";
		for (int i = 0; i < processes.size(); i++) {
			p_output
					<< std::to_string(processes.at(i).PID) + "\t"
							+ std::to_string(processes.at(i).a) + "\t"
							+ std::to_string(processes.at(i).s) + "\t\t"
							+ std::to_string(processes.at(i).prior) + "\n"; //helper;
		}
		p_output << "\nROUND ROBIN QUANTIUM:\t" + std::to_string(quant) + "\n";
		p_output
				<< "PRIORITY QUANTIUM:\t" + std::to_string(prior_quant)
						+ "\n\n\n";

		p_output << "RESULTS:\n";
		if (fcfs->symended) {
			p_output << "\tFCFS:\n";
			p_output
					<< "\t  AVERAGE WAITING TIME:\t\t"
							+ std::to_string(fcfs->t_mean()) + "\n";
			p_output
					<< "\t  AVERAGE TURN-AROUND TIME:\t"
							+ std::to_string(fcfs->ta_mean(processes)) + "\n\n";
		}
		if (rr->symended) {
			p_output << "\tROUND_ROBIN:\n";
			p_output
					<< "\t  AVERAGE WAITING TIME:\t\t"
							+ std::to_string(rr->t_mean()) + "\n";
			p_output
					<< "\t  AVERAGE TURN-AROUND TIME:\t"
							+ std::to_string(rr->ta_mean(processes)) + "\n\n";
		}
		if (pnp->symended) {
			p_output << "\tPRIORITY_NON_PREEMPTIVE:\n";
			p_output
					<< "\t  AVERAGE WAITING TIME:\t\t"
							+ std::to_string(pnp->t_mean()) + "\n";
			p_output
					<< "\t  AVERAGE TURN-AROUND TIME:\t"
							+ std::to_string(pnp->ta_mean(processes)) + "\n\n";
		}

		if (fcfs->symended) {
			p_output << "FCFS\n";
			p_output << "PID\tSTART\tFINISH\tBURST_TIME_LEFT\n";
			for (int i = 0; i < fcfs->ended.size(); i++) {
				p_output
						<< std::to_string(fcfs->ended.at(i).PID) + "\t"
								+ std::to_string(fcfs->ended.at(i).st) + "\t"
								+ std::to_string(fcfs->ended.at(i).ft) + "\t"
								+ std::to_string(fcfs->ended.at(i).s) + "\n"; //helper;
			}
			p_output << "\nPID\tWAITING_TIME\tFINISH_TIME_OF_WHOLE_PROCESS\n";
			for (int i = 0; i < fcfs->ended.size(); i++) {
				p_output
						<< std::to_string(fcfs->ended.at(i).PID) + "\t"
								+ std::to_string(fcfs->ended.at(i).t) + "\t\t"
								+ std::to_string(fcfs->ended.at(i).ft) + "\n";
			}
			p_output << "\n\n\n";
		}

		if (rr->symended) {
			p_output << "ROUND_ROBIN\n";
			p_output << "PID\tSTART\tFINISH\tBURST_TIME_LEFT\n";
			for (int i = 0; i < rr->ended.size(); i++) {
				p_output
						<< std::to_string(rr->ended.at(i).PID) + "\t"
								+ std::to_string(rr->ended.at(i).st) + "\t"
								+ std::to_string(rr->ended.at(i).ft) + "\t"
								+ std::to_string(rr->ended.at(i).s) + "\n"; //helper;
			}
			p_output << "\nPID\tWAITING_TIME\tFINISH_TIME_OF_WHOLE_PROCESS\n";
			for (int i = 0; i < rr->ended.size(); i++) {
				if (rr->ended.at(i).s == 0)
					p_output
							<< std::to_string(rr->ended.at(i).PID) + "\t"
									+ std::to_string(rr->ended.at(i).t) + "\t\t"
									+ std::to_string(rr->ended.at(i).ft) + "\n";
			}
			p_output << "\n\n\n";
		}

		if (pnp->symended) {
			p_output << "PRIORITY_NON_PREEMPTIVE\n";
			p_output << "PID\tSTART\tFINISH\tBURST_TIME_LEFT\n";
			for (int i = 0; i < pnp->ended.size(); i++) {
				p_output
						<< std::to_string(pnp->ended.at(i).PID) + "\t"
								+ std::to_string(pnp->ended.at(i).st) + "\t"
								+ std::to_string(pnp->ended.at(i).ft) + "\t"
								+ std::to_string(pnp->ended.at(i).s) + "\n"; //helper;
			}
			p_output << "\nPID\tWAITING_TIME\tFINISH_TIME_OF_WHOLE_PROCESS\n";
			for (int i = 0; i < pnp->ended.size(); i++) {
				p_output
						<< std::to_string(pnp->ended.at(i).PID) + "\t"
								+ std::to_string(pnp->ended.at(i).t) + "\t\t"
								+ std::to_string(pnp->ended.at(i).ft) + "\n";
			}
			p_output << "\n\n\n";
		}
	}
}

void load_processes() {

	std::vector<int> *linevec1 = new std::vector<int>();
	std::vector<int> *linevec2 = new std::vector<int>();
	std::vector<int> *linevec3 = new std::vector<int>();

	std::ifstream input("input\\processes_input.txt");
	std::string line;

	if (input) {
		processes_loaded = true;

		std::getline(input, line);
		int value;

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) && isspace(line.at(i)))
				processes_loaded = false;
			else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 0)
					settings_loaded = false;
			}
		}

		if (processes_loaded) {
			std::stringstream linestr(line);
			while (linestr >> value) {
				linevec1->push_back(value);
			}
		}

		std::getline(input, line);

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) && isspace(line.at(i)))
				processes_loaded = false;
			else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 1)
					settings_loaded = false;
			}
		}

		if (processes_loaded) {
			std::stringstream linestr(line);
			while (linestr >> value) {
				linevec2->push_back(value);
			}
		}

		std::getline(input, line);

		for (int i = 0; i < line.size(); i++) {
			if (isdigit(line.at(i)) && isspace(line.at(i)))
				processes_loaded = false;
			else if (isspace(line.at(i)) == false) {
				if (line.at(i) < 0)
					settings_loaded = false;
			}
		}

		if (processes_loaded) {
			std::stringstream linestr(line);
			while (linestr >> value) {
				linevec3->push_back(value);
			}
		}

		if (linevec1->size() == linevec2->size()
				&& linevec1->size() == linevec3->size()) {
			for (int i = 0; i < linevec1->size(); i++) {
				processes.push_back(
						Process(linevec1->at(i), linevec2->at(i), i,
								linevec3->at(i)));
			}
		} else
			processes_loaded = false;

		if (processes.size() < 15)
			processes_loaded = false;

		std::getline(input, line);

		if (isdigit(line.at(0))) {
			std::stringstream linestr(line);
			linestr >> value;
			prior_quant = value;
		} else
			processes_loaded = false;

		std::getline(input, line);

		if (isdigit(line.at(0))) {
			std::stringstream linestr(line);
			linestr >> value;
			quant = value;
		} else
			processes_loaded = false;
	}

	delete linevec1;
	delete linevec2;
	delete linevec3;

}

void video_output(Alghoritm *newfcfs);

int main() {

	load_processes();
	load_settings();

	if (processes_loaded && frames_loaded && settings_loaded) {
		Fcfs *fcfs;
		fcfs = new Fcfs(processes);

		Roundrobin *rr;
		rr = new Roundrobin(processes, quant);

		PriorityNP *pnp;
		pnp = new PriorityNP(processes, prior_quant);

		///////////////DLUGOSC SKALI///////////////
		std::thread FcfsThread(&Fcfs::alg, fcfs);
		while (fcfs->symended == false)
			fcfs->wait = false;
		FcfsThread.join();
		length = fcfs->trn + 10;
		delete fcfs;
		fcfs = new Fcfs(processes);

		int choice = 0;
		while (choice == 0) {
			system("cls");
			std::cout << "SYSTEMY OPERACYJNE - ALGORYTMY" << std::endl
					<< std::endl << std::endl;
			std::cout << "MENU\n";
			std::cout << "1. ALGORYTMY PLANOWANIA\n";
			std::cout << "10. WYJASNIENIE\n";
			std::cout << "0. ZAPIS I WYJSCIE\n";

			std::cin >> choice;
			while (std::cin.fail()) {
				system("cls");
				std::cout << "SYSTEMY OPERACYJNE - ALGORYTMY" << std::endl
						<< std::endl << std::endl;
				std::cout << "MENU\n";
				std::cout << "1. ALGORYTMY PLANOWANIA\n";
				std::cout << "2. ALGORYTMY WYMIANY STRON\n\n";
				std::cout << "10. WYJASNIENIE\n";
				std::cout << "0. ZAPIS I WYJSCIE\n";
				std::cout << "Bledny znak!" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> choice;
			}

			if (choice == 1) {
				choice = 0;
				while (choice == 0) {
					choice = 0;

					system("cls");
					std::cout << "SYSTEMY OPERACYJNE - ALGORYTMY" << std::endl
							<< std::endl << std::endl;
					std::cout << "MENU - ALGORYTMY PLANOWANIA\n";
					std::cout << "1. FCFS\n";
					std::cout << "2. Round Robin\n";
					std::cout << "3. Priorytetowy(bez wywlaszczen)\n\n";
					std::cout << "0. POWROT\n";

					std::cin >> choice;
					while (std::cin.fail()) {
						system("cls");
						std::cout << "SYSTEMY OPERACYJNE - ALGORYTMY"
								<< std::endl << std::endl << std::endl;
						std::cout << "MENU - ALGORYTMY PLANOWANIA\n";
						std::cout << "1. FCFS\n";
						std::cout << "2. Round Robin\n";
						std::cout << "3. Priorytetowy(bez wywlaszczen)\n\n";
						std::cout << "0. POWROT\n";
						std::cout << "Bledny znak!" << std::endl;
						std::cin.clear();
						std::cin.ignore(256, '\n');
						std::cin >> choice;
					}

					if (choice == 1) {
						delete fcfs;
						fcfs = new Fcfs(processes);
						std::thread FcfsThread(&Fcfs::alg, fcfs);
						video_output(fcfs);
						if (fcfs->symended == false) {
							while (fcfs->symended == false)
								fcfs->wait = false;
						}
						FcfsThread.join();
						cin.ignore();
						choice = 0;
					} else if (choice == 2) {
						delete rr;
						rr = new Roundrobin(processes, quant);
						std::thread RoundrobinThread(&Roundrobin::alg, rr);
						video_output(rr);
						if (rr->symended == false) {
							while (rr->symended == false)
								rr->wait = false;
						}
						RoundrobinThread.join();
						cin.ignore();
						choice = 0;
					} else if (choice == 3) {
						delete pnp;
						pnp = new PriorityNP(processes, prior_quant);
						std::thread PNPThread(&PriorityNP::alg, pnp);
						video_output(pnp);
						if (pnp->symended == false) {
							while (pnp->symended == false)
								pnp->wait = false;
						}
						PNPThread.join();
						cin.ignore();
						choice = 0;
					} else if (choice == 0) {
						choice++;
					} else {
						std::cout << "Bledny wybor, wcisnij ENTER."
								<< std::endl;
						choice = 0;
						std::cin.ignore();
						std::cin.ignore();
					}
				}

				choice = 0;
			} else if (choice == 0) {
				output(fcfs, rr, pnp);
				choice++;
			} else if (choice == 10) {
				system("CLS");

				std::cout << "Algorytmy planowania:\n";
				std::cout
						<< "\t1) FCFS - procesy obslugiwane po kolei od najwczesniejszego.\n";
				std::cout
						<< "\t2) Round Robin - kazdy proces w kolejce czekania obslugiwany przez kwant czasu, nastepnie wywlaszczany.\n";
				std::cout
						<< "\t3) Priorytetowy niewywlaszczajacy - proces z najwyzszym priorytetem obslugiwany pierwszy\n";
				std::cout
						<< "\t   (jesli dwa o tym samym priorytecie, wowczas obslugiwany ten o najmniejszym czasie przybycia).\n";
				std::cout
						<< "\t   W midzyczasie wszystkie procesy (w kolejce czekania / na procesorze) postarzane o 1 co kwant czasu\n";
				std::cout
						<< "\t   (im mniejsza wartosc, tym priorytet wyzszy; wartosc minimalna rowna 0).\n\n";

				std::cout << "Algorytmy zmiany stron:\n";
				std::cout
						<< "\t1) FIFO - wczytywanie nowej strony do ramki ze strona najwczesniej zaladowana.\n";
				std::cout
						<< "\t   (Niebieska wartosc obok numeru strony oznacza indeks ciagu odniesienia kiedy strona zostala wczytana)";
				std::cout
						<< "\t2) LRU - wczytywanie nowej strony do ramki ze strona najdawniej uzywana.\n";
				std::cout
						<< "\t   (Niebieska wartosc obok numeru strony oznacza indeks ciagu odniesienia kiedy strona zostala ostatnio uzyta)";
				std::cout
						<< "\t2) LFU - wczytywanie nowej strony do ramki ze strona najrzadziej uzywana\n";
				std::cout
						<< "\t   (jesli licznik uzyc taki sam w obu stronach, wtedy zamieniana ta wczytana najdawniej).\n";
				std::cout
						<< "\t   (Czerwona wartosc oznacza ilosc odwolan, ktore nastapily do danej chwili;\n";
				std::cout
						<< "\t   Niebieska wartosc odpowiada indeksowi ciagu odniesienia kiedy wartosc zostala wczytana)\n";
				std::cout
						<< "\t3) OPT - wczytywanie nowej strony do ramki ze strona najpozniej wczytywana w przyszlosci\n";
				std::cout
						<< "\t   (jesli zadna strona nie bedzie juz uzywana zamianiamy ta, ktora wczytana najdawniej).\n";
				std::cout
						<< "\t   (Czerwona wartosc oznacza indeks ciagu odniesienia najblizszego wystapienia strony;\n";
				std::cout
						<< "\t   Niebieska wartosc pojawia sie tylko gdy odwolanie do danej strony juz nie nastapi\n";
				std::cout
						<< "\t   i oznacza indeks ciagu odniesien kiedy zostala wczytana)\n\n\n";

				std::cout
						<< "Po uruchomieniu symulacji ustaw jako aktywne okno symulacji.\n";
				std::cout
						<< "Aby przejsc do nastepnego kroku w trakcie wykonywania nacisnij 'ENTER'.\n";
				std::cout << "Do poruszania po oknie uzywaj stralek.\n";
				std::cout
						<< "Kiedy symulacja zkonczy sie okno cie o tym powiadomi.\n";
				std::cout
						<< "Jesli zamkniesz okno w trakcie wykonywania symulacja zostanie przeprowadzona do konca.\n";
				std::cout
						<< "Wyniki uruchomionych symulacji zostana zapisane do folderu 'output'.\n";

				std::cin.ignore();
				std::cin.ignore();
				choice = 0;
			} else {
				std::cout << "Bledny wybor, wcisnij ENTER." << std::endl;
				choice = 0;
				std::cin.ignore();
				std::cin.ignore();
			}
		}

		delete fcfs;
		delete rr;
		delete pnp;
	} else {
		if (settings_loaded == false) {
			std::cout
					<< "Ustawienia zle wprowadzone lub brak pliku 'settings.txt'.\n";
			std::cout
					<< "Druga linijka oznacza szerokosc okna algorytmow planowania.\n";
			std::cout
					<< "Trzecia linijka oznacza wysokosc okna algorytmow planowania.\n";
			std::cout
					<< "Czwarta linijka oznacza szerokosc okna algorytmow zamiany stron.\n\n";
			std::cout
					<< "Wprowadzone dane musza byc liczbami calkowitymi!\n\n\n";
		}

		if (processes_loaded == false || frames_loaded == false) {
			std::cout
					<< "Wprowadzone dane nieprawidlowe lub brak plikow. Upewnij sie, ze wprowadziles:\n";
			std::cout
					<< "\t1) w pliku 'input\\processes_input.txt' co najmniej 15 procesow i dla kazdego z nich informacje:\n";
			std::cout << "\t\t; -pierwsza linia pliku - czas przybycia,\n";
			std::cout
					<< "\t\t; -druga linia pliku - czas trwania fazy procesu,\n";
			std::cout << "\t\t; -trzecia linia pliku - priorytet procesu,\n";
			std::cout
					<< "\t   oraz w inijce 4 kwant czasu dla algorytmu Priorytetowego, w 5 linijce kwant dla algorytmu Round Robin\n\n";

			std::cout
					<< "\t2) w pliku 'input\\frames_input.txt' co najmniej 20 stron w linii pierwszej oraz ilosc ramek w drugiej.\n\n";

			std::cout << "Wprowadzone dane musza byc liczbami calkowitymi!\n\n";
		}
		cin.ignore();
	}

	return 0;
}

struct Event {
public:
	sf::CircleShape triangle;
	sf::Text PID;
	int charPID;

	Event(sf::CircleShape triangle, sf::Text PID, int charPID) {
		this->triangle = triangle;
		this->PID = PID;
		this->charPID = charPID;
	}
};

struct Rep {
public:
	sf::RectangleShape rectangle;
	sf::Text PID;
	int charPID;

	Rep(sf::RectangleShape rectangle, sf::Text PID, int charPID) {
		this->rectangle = rectangle;
		this->PID = PID;
		this->charPID = charPID;
	}
};

void video_output(Alghoritm *newfcfs) {
	sf::Font font;
	font.loadFromFile("Oswald-Medium.ttf");
	if (!font.loadFromFile("Oswald-Medium.ttf"))
		std::cout << "Could not load font." << std::endl;

	////////////////////////////////////////////////////////////////////////////////
	sf::RenderWindow window(sf::VideoMode(width, heigth), "FCFS");
	sf::View view(sf::Vector2f(width / 2, 500 - heigth / 2),
			sf::Vector2f(width, heigth));
	window.setView(view);
	int viewX = 0;

	////////////////////OS CZASU///////////////////////
	sf::Text timeline[length + 1];
	for (int i = 0; i < length; i++) {
		timeline[i] = sf::Text();
		timeline[i].setString(to_string(i));
		timeline[i].setCharacterSize(10);
		timeline[i].setFillColor(sf::Color::Black);
		timeline[i].setFont(font);
		timeline[i].setPosition(sf::Vector2f((i) * 20 + 62, 260));
	}
	///////////////////TABELA//////////////////////////
	sf::Text tableP[processes.size() + 2][4];

	tableP[0][0] = sf::Text();
	tableP[0][0].setString("PID");
	tableP[0][0].setCharacterSize(13);
	tableP[0][0].setFillColor(sf::Color::Black);
	tableP[0][0].setFont(font);
	tableP[0][0].setPosition(sf::Vector2f(10, 10 + 500 - heigth));

	tableP[0][1] = sf::Text();
	tableP[0][1].setString("Czas przyjscia");
	tableP[0][1].setCharacterSize(13);
	tableP[0][1].setFillColor(sf::Color::Black);
	tableP[0][1].setFont(font);
	tableP[0][1].setPosition(sf::Vector2f(10, 40 + 500 - heigth));

	tableP[0][2] = sf::Text();
	tableP[0][2].setString("Czas wykonywania");
	tableP[0][2].setCharacterSize(13);
	tableP[0][2].setFillColor(sf::Color::Black);
	tableP[0][2].setFont(font);
	tableP[0][2].setPosition(sf::Vector2f(10, 70 + 500 - heigth));

	for (int i = 0; i < processes.size(); i++) {
		sf::Text processP;
		processP.setString(std::to_string(processes.at(i).PID));
		processP.setCharacterSize(13);
		processP.setFillColor(sf::Color::Black);
		processP.setFont(font);
		processP.setPosition(sf::Vector2f(130 + i * 30, 10 + 500 - heigth));
		tableP[i + 1][0] = processP;
		processP.setString(std::to_string(processes.at(i).a));
		processP.setPosition(sf::Vector2f(130 + i * 30, 40 + 500 - heigth));
		tableP[i + 1][1] = processP;
		processP.setString(std::to_string(processes.at(i).s));
		processP.setPosition(sf::Vector2f(130 + i * 30, 70 + 500 - heigth));
		tableP[i + 1][2] = processP;
	}

	sf::VertexArray tableline1(sf::Lines, 2);
	tableline1[0].position = sf::Vector2f(10, 30 + 500 - heigth);
	tableline1[0].color = sf::Color::Black;
	tableline1[1].position = sf::Vector2f(130 + processes.size() * 30,
			30 + 500 - heigth);
	tableline1[1].color = sf::Color::Black;

	sf::VertexArray tableline2(sf::Lines, 2);
	tableline2[0].position = sf::Vector2f(120, 10 + 500 - heigth);
	tableline2[0].color = sf::Color::Black;
	tableline2[1].position = sf::Vector2f(120, 90 + 500 - heigth);
	tableline2[1].color = sf::Color::Black;

	/////////////////////////////OSIE////////////////////////////////////
	sf::Text ready;
	ready.setString("Nowe\nprocesy\nw READY");
	ready.setCharacterSize(10);
	ready.setFillColor(sf::Color::Black);
	ready.setFont(font);
	ready.setPosition(sf::Vector2f(10, 175));

	sf::Text pnow;
	pnow.setString("Proces\nw chwili t");
	pnow.setCharacterSize(10);
	pnow.setFillColor(sf::Color::Black);
	pnow.setFont(font);
	pnow.setPosition(sf::Vector2f(10, 220));

	sf::Text timet;
	timet.setString("Os\nczasu t");
	timet.setCharacterSize(10);
	timet.setFillColor(sf::Color::Black);
	timet.setFont(font);
	timet.setPosition(sf::Vector2f(10, 250));

	///////////////////////////ZDARZENIA///////////////////////////////////
	sf::Text eventt;
	eventt.setString("Zdarzenia");
	eventt.setCharacterSize(10);
	eventt.setFillColor(sf::Color::Black);
	eventt.setFont(font);
	eventt.setPosition(sf::Vector2f(110 + viewX, 300));

	sf::VertexArray eventtline(sf::Lines, 2);
	eventtline[0].position = sf::Vector2f(30 + viewX, 320);
	eventtline[0].color = sf::Color::Black;
	eventtline[1].position = sf::Vector2f(230 + viewX, 320);
	eventtline[1].color = sf::Color::Black;

	std::vector<Event> vecEvent;
	std::vector<Rep> vecProcess;
	////////////////////////////////////////////////////////////////////////

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right
						&& viewX < length * 20) {
					view.move(100, 0);
					viewX += 100;
				} else if (event.key.code == sf::Keyboard::Left && viewX != 0) {
					view.move(-100, 0);
					viewX += -100;
				} else if (event.key.code == sf::Keyboard::Enter) {
					newfcfs->wait = false;
				}
			}

		}
		window.clear(sf::Color::White);
		window.setView(view);
		//////////////////////TABELA c.d./////////////////////
		for (int i = 0; i < processes.size() + 1; i++) {
			window.draw(tableP[i][0]);
			window.draw(tableP[i][1]);
			window.draw(tableP[i][2]);
		}
		window.draw(tableline1);
		window.draw(tableline2);
		//////////////////////OSIE c.d.///////////////////////
		window.draw(ready);
		window.draw(pnow);
		window.draw(timet);
		/////////////////////////////////////////////////

		//////////////////////LICZNIK ZDARZEN///////////////////////
		int ecounter = 0;
		////////////////////////////ZDARZENIA///////////////////////////
		window.draw(eventt);
		window.draw(eventtline);

		///////////////////////////OS CZASU/////////////////////////
		for (int i = 0; i < length; i++)
			window.draw(timeline[i]);

		//////////////////////DRAW EVENT///////////////////////////
		for (int i = 0; i < vecEvent.size(); i++) {
			window.draw(vecEvent.at(i).triangle);
			window.draw(vecEvent.at(i).PID);
		}

		for (int i = 0; i < vecProcess.size(); i++) {
			window.draw(vecProcess.at(i).rectangle);
			window.draw(vecProcess.at(i).PID);
		}

		for (int i = 0; i < processes.size(); i++) {
			///////////////////////ZNACZNIK WEJSCIA DO READY//////////////////////
			if (processes.at(i).a <= newfcfs->trn) {
				bool check = true;
				for (int j = 0; j < vecEvent.size(); j++)
					if (processes.at(i).PID == vecEvent.at(j).charPID)
						check = false;

				if (check) {
					sf::CircleShape triangle;
					triangle.setRadius(5.f);
					triangle.setPointCount(3);
					triangle.setFillColor(sf::Color::Red);
					triangle.setOutlineColor(sf::Color::Black);
					triangle.setOutlineThickness(0.5);
					triangle.rotate(180);
					triangle.setPosition(
							sf::Vector2f(processes.at(i).a * 20 + 69, 198));

					int repos = 0;
					for (int j = i + 1; j < processes.size(); j++) {
						if (processes.at(i).a == processes.at(j).a)
							repos++;
					}

					sf::Text PID;
					PID.setString(std::to_string(processes.at(i).PID));
					PID.setCharacterSize(13);
					PID.setFillColor(sf::Color::Black);
					PID.setFont(font);
					if (processes.at(i).PID < 10)
						PID.setPosition(
								sf::Vector2f(processes.at(i).a * 20 + 59,
										170 - repos * 13));
					else if (processes.at(i).PID > 9
							&& processes.at(i).PID < 100)
						PID.setPosition(
								sf::Vector2f(processes.at(i).a * 20 + 57,
										170 - repos * 13));
					else if (processes.at(i).PID >= 100)
						PID.setPosition(
								sf::Vector2f(processes.at(i).a * 20 + 53,
										170 - repos * 13));

					vecEvent.push_back(
							Event(triangle, PID, processes.at(i).PID));
				}
			}
			/////////////////////////////ZDARZENIE READY//////////////////////////////
			if (newfcfs->ended.size() == 0) {
				if (processes.at(i).a <= newfcfs->trn) {
					std::string readys = "Proces w kolejce READY:"
							+ std::to_string(processes.at(i).PID);
					sf::Text readyt;
					readyt.setString(readys);
					readyt.setCharacterSize(10);
					readyt.setFillColor(sf::Color::Black);
					readyt.setFont(font);
					readyt.setPosition(
							sf::Vector2f(30 + viewX, 325 + ecounter * 15));
					window.draw(readyt);
					ecounter++;
				}
			} else if (processes.at(i).a <= newfcfs->trn
					&& processes.at(i).a > newfcfs->ended.back().st) {
				std::string readys = "Proces w kolejce READY:"
						+ std::to_string(processes.at(i).PID);
				sf::Text readyt;
				readyt.setString(readys);
				readyt.setCharacterSize(10);
				readyt.setFillColor(sf::Color::Black);
				readyt.setFont(font);
				readyt.setPosition(
						sf::Vector2f(30 + viewX, 325 + ecounter * 15));
				window.draw(readyt);
				ecounter++;
			}

			if (newfcfs->ended.size() > 1) {
				if (processes.at(i).a <= newfcfs->trn
						&& newfcfs->ended.at(newfcfs->ended.size() - 2).ft
								!= newfcfs->ended.at(newfcfs->ended.size() - 1).st
						&& processes.at(i).a
								> newfcfs->ended.at(newfcfs->ended.size() - 2).st) {
					std::string readys = "Proces w kolejce READY:"
							+ std::to_string(processes.at(i).PID);
					sf::Text readyt;
					readyt.setString(readys);
					readyt.setCharacterSize(10);
					readyt.setFillColor(sf::Color::Black);
					readyt.setFont(font);
					readyt.setPosition(
							sf::Vector2f(30 + viewX, 325 + ecounter * 15));
					window.draw(readyt);
					ecounter++;
				}
			}
		}
		////////////////////////////ZDARZENIE PROCES ZAKONCZONY////////////////////
		for (int i = 0; i < newfcfs->ended.size(); i++) {
			if (newfcfs->ended.at(i).s == 0
					&& newfcfs->ended.at(i).ft == newfcfs->trn) {
				std::string readys = "Proces zakonczony:"
						+ std::to_string(newfcfs->ended.at(i).PID);
				sf::Text readyt;
				readyt.setString(readys);
				readyt.setCharacterSize(10);
				readyt.setFillColor(sf::Color::Black);
				readyt.setFont(font);
				readyt.setPosition(
						sf::Vector2f(30 + viewX, 325 + ecounter * 15));
				window.draw(readyt);
				ecounter++;
			}
		}
		///////////////////////////////RYSOWANIE PROCESU////////////////////////
		for (int i = 0; i < newfcfs->ended.size(); i++) {
			bool check = true;
			for (int j = 0; j < vecProcess.size(); j++)
				if (newfcfs->ended.at(i).PID == vecProcess.at(j).charPID)
					check = false;

			if (check) {

				///////////////////////RYSOWANIE ZNACZNIKA/////////////////////////////
				int wideness = newfcfs->ended.at(i).ft * 20
						- newfcfs->ended.at(i).st * 20;
				sf::RectangleShape rectangle;
				rectangle.setSize(sf::Vector2f(wideness - 2, 50));
				rectangle.setOutlineColor(sf::Color::Black);
				rectangle.setOutlineThickness(2);
				rectangle.setPosition(
						sf::Vector2f((newfcfs->ended.at(i).st) * 20 + 65, 200)); //(trn2+4)*10+50, 200);

				/////////////////////////////PID/////////////////////////////////////
				sf::Text PID;
				PID.setString(std::to_string(newfcfs->ended.at(i).PID));
				PID.setCharacterSize(18);
				if (newfcfs->ended.at(i).s != 0)
					PID.setFillColor(sf::Color::Black);
				else {
					PID.setFillColor(sf::Color::Red);
					PID.setOutlineColor(sf::Color::Black);
					PID.setOutlineThickness(0.7);
				}
				PID.setFont(font);
				if (newfcfs->ended.at(i).PID < 10)
					PID.setPosition(
							sf::Vector2f(
									(newfcfs->ended.at(i).st) * 20
											+ wideness / 2 + 60, 215));
				else if (newfcfs->ended.at(i).PID > 9
						&& newfcfs->ended.at(i).PID < 100)
					PID.setPosition(
							sf::Vector2f(
									(newfcfs->ended.at(i).st) * 20
											+ wideness / 2 + 56, 215));
				else if (newfcfs->ended.at(i).PID >= 100)
					PID.setPosition(
							sf::Vector2f(
									(newfcfs->ended.at(i).st) * 20
											+ wideness / 2 + 51, 215));

				vecProcess.push_back(
						Rep(rectangle, PID, newfcfs->ended.at(i).PID));
			}
		}
		///////////////////////////ZAKONCZENIE/////////////////////////////???
		if (newfcfs->symended) {
			sf::Text closesym;
			closesym.setString("Symulacja zakonczona, mozesz zamknac okno.");
			closesym.setCharacterSize(17);
			closesym.setFillColor(sf::Color::Red);
			closesym.setOutlineColor(sf::Color::Black);
			closesym.setOutlineThickness(0.3);
			closesym.setFont(font);
			closesym.setPosition(sf::Vector2f(30 + viewX, 325 + ecounter * 15));
			window.draw(closesym);

			std::string result_string = "Sredni czas czekania: "
					+ std::to_string(newfcfs->t_mean())
					+ "\nSredni czas przetwarzania: "
					+ std::to_string(newfcfs->ta_mean(processes));
			sf::Text result;
			result.setString(result_string);
			result.setCharacterSize(20);
			result.setFillColor(sf::Color::Black);
			result.setFont(font);
			result.setPosition(sf::Vector2f(430 + viewX, 325));
			window.draw(result);
		}

		window.display();
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
