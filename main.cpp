#include <QGuiApplication>
#include <QQmlApplicationEngine>

//#define KLIM_DEBUG


#if defined KLIM_DEBUG
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Utils/serialization.h"
#include "Utils/typeconvertors.h"

void dumpFigures( const std::vector<chess::ItemPtr>& vec )
{
    /*for ( auto& item : vec)
    {
        chess::Item& it = *item.get();
        std::cout << chess_utils::convertTypeToString(it.getType()) << "  position  row :" << it.getPosition().row_ << " col : " << it.getPosition().col_
                  << std::endl;
    }
    return;*/

    std::vector<std::size_t> rows{1,2,3,4,5,6,7,8};
    std::vector<std::size_t> cols{8,7,6,5,4,3,2,1};

    std::cout <<std::endl;
    std::size_t width = 15;

    for ( auto col : cols )
    {
        std::cout << col << "  ";
        std::vector<chess::Item*> rowItems;
        for (auto& it : vec)
        {
            if ( it.get()->getPosition().col_ == col )
                rowItems.push_back(it.get());
        }

        if (rowItems.empty())
        {
            std::cout << std::endl;
            continue;
        }

        std::sort(rowItems.begin(), rowItems.end(), [](const auto it1, const auto it2){
            return it1->getPosition().col_ < it2->getPosition().col_;
        });

        for (auto row : rows)
        {
            auto foundIt = std::find_if(rowItems.begin(), rowItems.end(), [row](const auto p){
                return p->getPosition().row_ == row;
            });

            if (foundIt != rowItems.end())
            {
                std::string field = chess_utils::convertTypeToString( (*foundIt)->getType() )
                            + " " + chess_utils::convertSideToString((*foundIt)->getSide());
                std::cout<< std::setw(width)<< field;
            }
            else
                std::cout<< std::setw(width) << "";
        }
        std::cout << std::endl;
    }

    for ( auto col : cols)
        std::cout<< std::setw(width)<< col;

    std::cout<< std::endl;
}

#endif

int main(int argc, char *argv[])
{

#if defined KLIM_DEBUG
    auto figures = chess_utils::derializeFromJSON( "://Configs//StartConfiguration.json" );

    dumpFigures(figures);

    return 1;
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
