#include	"card_deck.hpp"


int myrandom (int i) { return std::rand()%i;}

string card2str(int c) {
	std::stringstream buffer;
	if(c<0) {
		return "undefined";
	} else {
		switch (c%4) {
			case 0:
				buffer	<< "S";
				break;
			case 1:
				buffer	<< "H";
				break;
			case 2:
				buffer	<< "D";
				break;
			case 3:
				buffer	<< "C";
				break;
			default:
				break;
		}

		switch (c/4) {
			case 0:
				buffer	<< "A";
				break;
			case 1:
				buffer	<< "K";
				break;
			case 2:
				buffer	<< "Q";
				break;
			case 3:
				buffer	<< "V";
				break;
			default:
				buffer	<<  14 - (c/4);
				break;
		}
	}
	
	return buffer.str();
}
/*
const wchar_t* card2unistr(int c) {
	wchar_t* buffer=(wchar_t*)malloc(100);
	
	if(c<0) {
		return L"undefined";
	} else {
		switch (c%4) {
			case 0:
				//buffer={' ',0xE2,0x99,0xA0,' '};
				buffer=L"\u2660";
				break;
			case 1:
				//buffer={' ',0xE2,0x99,0xA5,' '};
				buffer=L"\u2665";
				break;
			case 2:

				//buffer={' ',0xE2,0x99,0xA6,' '};
				buffer=L"\u2666";
				break;
			case 3:

				//buffer={' ',0xE2,0x99,0xA3,' '};
				buffer=L"\u2663";
				break;
			default:
				break;
		}

		switch (c/4) {
			case 0:
				buffer=wcscat(buffer,L"A");
				break;
			case 1:
				buffer=wcscat(buffer,L"K");
				break;
			case 2:
				buffer=wcscat(buffer,L"Q");
				break;
			case 3:
				buffer=wcscat(buffer,L"V");
				break;
			default:
				int value= 14 - (c/4);			
				buffer=wcscat(buffer,to_wstring(value).c_str());
				break;
		}
	}
	
	return buffer;
}*/

std::wstring card2unistr(int c) {
	std::wstring buffer=(wchar_t*)malloc(100);
	
	if(c<0) {
		return L"undefined";
	} else {
		switch (c%4) {
			case 0:
				//buffer={' ',0xE2,0x99,0xA0,' '};
				buffer=L"  \u2660 ";
				break;
			case 1:
				//buffer={' ',0xE2,0x99,0xA5,' '};
				buffer=L"  \u2665 ";
				break;
			case 2:

				//buffer={' ',0xE2,0x99,0xA6,' '};
				buffer=L"  \u2666 ";
				break;
			case 3:

				//buffer={' ',0xE2,0x99,0xA3,' '};
				buffer=L"  \u2663 ";
				break;
			default:
				break;
		}

		switch (c/4) {
			case 0:
				buffer=buffer+L"A";
				break;
			case 1:
				buffer=buffer+L"K";
				break;
			case 2:
				buffer=buffer+L"Q";
				break;
			case 3:
				buffer=buffer+L"V";
				break;
			default:
				int value= 14 - (c/4);			
				buffer=buffer+to_wstring(value);
				break;
		}
	}
	
	return buffer;
}
