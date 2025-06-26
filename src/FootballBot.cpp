#include "../includes/FootballBot.hpp"
#include "../includes/Client.hpp"
#include "../includes/Server.hpp"
#include <iostream>

FootballBot::FootballBot() {
    initialize();
    std::cout << "FootballBot başlatıldı - 99 futbolcu veritabanı hazır." << std::endl;
}

FootballBot::~FootballBot() {
    std::cout << "FootballBot sonlandırılıyor." << std::endl;
}

void FootballBot::initialize() {
    _legendaryFootballers["01"] = "Oliver Kahn - Bayern Munich & Almanya efsanesi";
    _legendaryFootballers["02"] = "Cafu - Brezilya & AC Milan efsane sağ beki";
    _legendaryFootballers["03"] = "Paolo Maldini - AC Milan & İtalya efsanesi";
    _legendaryFootballers["04"] = "Sergio Ramos - Real Madrid & İspanya defans oyuncusu";
    _legendaryFootballers["05"] = "Zinedine Zidane - Fransa & Real Madrid maestrosu";
    _legendaryFootballers["06"] = "Franco Baresi - AC Milan & İtalya defans oyuncusu";
    _legendaryFootballers["07"] = "Cristiano Ronaldo - Portekiz, Man Utd, Real Madrid yıldızı";
    _legendaryFootballers["08"] = "Andrés Iniesta - Barcelona & İspanya orta saha dehası";
    _legendaryFootballers["09"] = "Ronaldo (R9) - Brezilya forvet, 'El Fenomeno'";
    _legendaryFootballers["10"] = "Lionel Messi - Arjantin & Barcelona efsanesi";
    _legendaryFootballers["11"] = "Didier Drogba - Chelsea & Fildişi Sahili forvet oyuncusu";
    _legendaryFootballers["12"] = "Marcelo Vieira - Brezilya & Real Madrid sol beki";
    _legendaryFootballers["13"] = "Michael Ballack - Almanya & Chelsea orta saha oyuncusu";
    _legendaryFootballers["14"] = "Johan Cruyff - Hollanda & Barcelona yenilikçisi";
    _legendaryFootballers["15"] = "Arda Güler - DÜNYANIN EN İYİSİ";
    _legendaryFootballers["16"] = "Roy Keane - Man Utd & İrlanda orta saha oyuncusu";
    _legendaryFootballers["17"] = "Luis Figo - Portekiz & Real Madrid kanat oyuncusu";
    _legendaryFootballers["18"] = "Paul Scholes - Man Utd & İngiltere orta saha maestrosu";
    _legendaryFootballers["19"] = "Lionel Messi - İlk Barcelona yılları";
    _legendaryFootballers["20"] = "Deco - Portekiz & Barcelona orta saha oyuncusu";
    _legendaryFootballers["21"] = "Andrea Pirlo - İtalya & Juventus derin oyun kurucu";
    _legendaryFootballers["22"] = "Kaká - Brezilya & AC Milan oyun kurucu";
    _legendaryFootballers["23"] = "David Beckham - İngiltere & Man Utd sağ orta saha";
    _legendaryFootballers["24"] = "Marco Materazzi - İtalya & Inter defans oyuncusu";
    _legendaryFootballers["25"] = "Gianluigi Buffon - İtalya & Juventus kalecisi";
    _legendaryFootballers["26"] = "John Terry - Chelsea & İngiltere defans oyuncusu";
    _legendaryFootballers["27"] = "David Trezeguet - Fransa & Juventus forvet oyuncusu";
    _legendaryFootballers["28"] = "Claude Makélélé - Fransa & Chelsea defansif orta saha";
    _legendaryFootballers["29"] = "Nicolas Anelka - Fransa & Chelsea forvet oyuncusu";
    _legendaryFootballers["30"] = "Lionel Messi - Barcelona ilk günleri (2006)";
    _legendaryFootballers["31"] = "Bastian Schweinsteiger - Almanya & Bayern Munich orta saha";
    _legendaryFootballers["32"] = "Carlos Tevez - Arjantin, Man Utd & Man City forvet";
    _legendaryFootballers["33"] = "Roberto Carlos - Brezilya & Real Madrid sol beki";
    _legendaryFootballers["34"] = "Nuri Şahin - Dortmund & Türkiye orta saha oyuncusu";
    _legendaryFootballers["35"] = "Philippe Coutinho - İlk Liverpool yılları";
    _legendaryFootballers["36"] = "Roberto Firmino - İlk Liverpool günleri";
    _legendaryFootballers["37"] = "Steffen Freund - Tottenham & Almanya orta saha oyuncusu";
    _legendaryFootballers["38"] = "Karim Benzema - İlk Real Madrid yılları";
    _legendaryFootballers["39"] = "Nicolas Anelka - İlk Arsenal günleri";
    _legendaryFootballers["40"] = "Mats Hummels - İlk Dortmund günleri";
    _legendaryFootballers["41"] = "Willy Caballero - Chelsea kalecisi";
    _legendaryFootballers["42"] = "Yaya Touré - Man City & Fildişi Sahili orta saha";
    _legendaryFootballers["43"] = "Sergio Agüero - İlk Man City yılları";
    _legendaryFootballers["44"] = "Ivan Perišić - Hırvatistan & Inter kanat oyuncusu";
    _legendaryFootballers["45"] = "Mario Balotelli - İtalya & Man City forvet oyuncusu";
    _legendaryFootballers["46"] = "Rosicky - Arsenal & Çek Cumhuriyeti orta saha oyuncusu";
    _legendaryFootballers["47"] = "Juan Foyth - Tottenham defans oyuncusu";
    _legendaryFootballers["48"] = "Ismaël Bennacer - AC Milan orta saha oyuncusu";
    _legendaryFootballers["49"] = "Donny van de Beek - Hollanda & Ajax orta saha oyuncusu";
    _legendaryFootballers["50"] = "Emre Can - Liverpool & Almanya orta saha oyuncusu";
    _legendaryFootballers["51"] = "David Luiz - Brezilya & Chelsea defans oyuncusu";
    _legendaryFootballers["52"] = "Nicklas Bendtner - Danimarka & Arsenal forvet oyuncusu";
    _legendaryFootballers["53"] = "Wojciech Szczęsny - Arsenal & Polonya kalecisi";
    _legendaryFootballers["54"] = "Jonjo Shelvey - Liverpool orta saha oyuncusu";
    _legendaryFootballers["55"] = "Bixente Lizarazu - Bayern Munich & Fransa defans oyuncusu";
    _legendaryFootballers["56"] = "Riyad Mahrez - Leicester & Cezayir kanat oyuncusu";
    _legendaryFootballers["57"] = "Gennaro Gattuso - AC Milan & İtalya orta saha oyuncusu";
    _legendaryFootballers["58"] = "Christian Pulisic - Chelsea & ABD kanat oyuncusu";
    _legendaryFootballers["59"] = "Fernando Torres - İspanya & Liverpool forvet oyuncusu";
    _legendaryFootballers["60"] = "John O'Shea - Man Utd & İrlanda çok yönlü oyuncu";
    _legendaryFootballers["61"] = "Luka Modrić - Real Madrid & Hırvatistan orta saha oyuncusu";
    _legendaryFootballers["62"] = "Henrikh Mkhitaryan - Ermenistan orta saha oyuncusu";
    _legendaryFootballers["63"] = "Xherdan Shaqiri - İsviçre orta saha oyuncusu";
    _legendaryFootballers["64"] = "Emiliano Martínez - Arjantin & Aston Villa kalecisi";
    _legendaryFootballers["65"] = "James Rodríguez - Kolombiya & Real Madrid orta saha";
    _legendaryFootballers["66"] = "Trent Alexander-Arnold - Liverpool sağ bek";
    _legendaryFootballers["67"] = "Harvey Elliott - Liverpool genç yetenek";
    _legendaryFootballers["68"] = "Axel Tuanzebe - Man Utd defans oyuncusu";
    _legendaryFootballers["69"] = "Iker Muniain - Athletic Bilbao forvet oyuncusu";
    _legendaryFootballers["70"] = "Adama Traoré - Wolves & İspanya kanat oyuncusu";
    _legendaryFootballers["71"] = "Lucas Moura - Tottenham & Brezilya kanat oyuncusu";
    _legendaryFootballers["72"] = "Josip Iličić - Slovenya & Atalanta forvet oyuncusu";
    _legendaryFootballers["73"] = "Mateo Kovačić - Hırvatistan & Chelsea orta saha oyuncusu";
    _legendaryFootballers["74"] = "Victor Osimhen - Nijerya & Napoli forvet oyuncusu";
    _legendaryFootballers["75"] = "Alisson Becker - Brezilya & Liverpool kalecisi";
    _legendaryFootballers["76"] = "Hakan Çalhanoğlu - Türkiye & AC Milan orta saha oyuncusu";
    _legendaryFootballers["77"] = "Henrikh Mkhitaryan - Ermenistan & Roma orta saha oyuncusu";
    _legendaryFootballers["78"] = "Kalidou Koulibaly - Senegal & Napoli defans oyuncusu";
    _legendaryFootballers["79"] = "Milan Škriniar - Slovakya & Inter defans oyuncusu";
    _legendaryFootballers["80"] = "Ronaldinho - Brezilya & Barcelona sihirbazı";
    _legendaryFootballers["81"] = "Parma Calcio Gençlik Numarası";
    _legendaryFootballers["82"] = "Igor Akinfeev - Rusya & CSKA Moskova kalecisi";
    _legendaryFootballers["83"] = "Jesus Navas - İspanya & Man City kanat oyuncusu";
    _legendaryFootballers["84"] = "Weston McKennie - ABD & Juventus orta saha oyuncusu";
    _legendaryFootballers["85"] = "Conor Coady - İngiltere & Wolves defans oyuncusu";
    _legendaryFootballers["86"] = "Jack Grealish - İngiltere & Aston Villa kaptanı";
    _legendaryFootballers["87"] = "Marcel Sabitzer - Avusturya & RB Leipzig orta saha oyuncusu";
    _legendaryFootballers["88"] = "Goran Pandev - Kuzey Makedonya & Genoa forvet oyuncusu";
    _legendaryFootballers["89"] = "Antonio Candreva - İtalya & Inter kanat oyuncusu";
    _legendaryFootballers["90"] = "Romelu Lukaku - Belçika & Inter forvet oyuncusu";
    _legendaryFootballers["91"] = "Ian Wright - Arsenal efsanesi (doğum yılı 1963)";
    _legendaryFootballers["92"] = "Naby Keïta - Gine & Liverpool orta saha oyuncusu";
    _legendaryFootballers["93"] = "Matteo Darmian - İtalya & Man Utd defans oyuncusu";
    _legendaryFootballers["94"] = "Dejan Lovren - Hırvatistan & Liverpool defans oyuncusu";
    _legendaryFootballers["95"] = "Breel Embolo - İsviçre & Borussia Mönchengladbach";
    _legendaryFootballers["96"] = "Adrien Rabiot - Fransa & Juventus orta saha oyuncusu";
    _legendaryFootballers["97"] = "Joshua Zirkzee - Hollanda forvet oyuncusu";
    _legendaryFootballers["98"] = "Felipe Anderson - Brezilya & West Ham kanat oyuncusu";
    _legendaryFootballers["99"] = "Ronaldo (R9) - AC Milan günleri";
}

std::string FootballBot::getFootballerInfo(const std::string& jerseyNumber) const {
    std::map<std::string, std::string>::const_iterator it = _legendaryFootballers.find(jerseyNumber);
    if (it != _legendaryFootballers.end()) {
        return it->second;
    }
    return "Bu numara için futbolcu bulunamadı: " + jerseyNumber;
}

bool FootballBot::hasFootballer(const std::string& jerseyNumber) const {
    return _legendaryFootballers.find(jerseyNumber) != _legendaryFootballers.end();
} 

void Server::handleBot(const std::string& channel, Client& sender, const std::string& command) {
    std::cout << "Bot komutu alındı: " << command << " (Kanal: " << (channel.empty() ? "ana pencere/özel" : channel) << ", Gönderen: " << sender.getNickname() << ")" << std::endl;
    
    std::string number = command;
    
    if (command.empty()) {
        std::string response = ":" + _serverName + " PRIVMSG " + sender.getNickname() + 
                               " :Kullanım: /bot <numara> veya sadece <numara>. Örnek: /bot 07 veya sadece 7";
        sender.sendMessage(response);
        return;
    }
    
    if (command.length() == 1 && isdigit(command[0])) {
        number = "0" + command;
    }
    
    if (number.length() != 2 || !isdigit(number[0]) || !isdigit(number[1])) {
        std::string response = ":" + _serverName + " PRIVMSG " + sender.getNickname() + 
                              " :Lütfen 01-99 arası bir numara girin. Örnek: /bot 07 veya sadece 7";
        sender.sendMessage(response);
        return;
    }
    
    if (_footballBot.hasFootballer(number)) {
        std::string playerInfo = _footballBot.getFootballerInfo(number);
        
            std::string response = ":" + _serverName + " PRIVMSG " + sender.getNickname() + 
                                  " :" + number + " -> " + playerInfo;
            sender.sendMessage(response);
            std::cout << "Bot yanıtı özel/ana pencerede gönderildi: " << number << " -> " << playerInfo << std::endl;
    } else {
        std::string response = ":" + _serverName + " PRIVMSG " + sender.getNickname() + 
                              " :Bu numara için futbolcu bulunamadı: " + number;
        sender.sendMessage(response);
        std::cout << "Futbolcu bulunamadı: " << number << std::endl;
    }
}
