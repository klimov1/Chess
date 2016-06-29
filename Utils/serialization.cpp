#include "serialization.h"
#include "typeconvertors.h"
#include "ChessEngine/itemfactory.h"

#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QString"

namespace chess_utils {

// serialize items into file
/*
bool serializeToJSON(const std::vector<chess::ItemPtr>& board, const std::string& fileName)
{


    return true;
}
*/

std::vector<chess::ItemPtr> derializeFromJSON(const std::string& fileName)
{
    QFile file(QString::fromStdString(fileName));
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return {};

    QString fileContent = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
    QJsonObject mainObject = d.object();

    std::vector<chess::ItemPtr> res;
    auto types = getAllTypesAsString();
    for (const auto& typeStr : types )
    {
        auto itemArrayIt = mainObject.find(QString::fromStdString(typeStr));
        if (itemArrayIt == mainObject.end() )
            continue;

        auto itemArray = itemArrayIt.value().toArray();
        for(const auto& it : itemArray)
        {
            auto itemConfig = it.toObject();
            std::string sideStr = itemConfig.find("Side").value().toString().toStdString();
            auto positionObj = itemConfig.find("Position").value().toObject();


            chess::Position pos{ positionObj["row"].toString().toUInt(),
                                 positionObj["col"].toString().toUInt() };

            res.push_back(chess::createItem( parseTypeFromString(typeStr), parseSideFromString(sideStr), pos));
        }
    }

    return res;
}

}

