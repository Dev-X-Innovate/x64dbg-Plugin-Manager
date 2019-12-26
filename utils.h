// Copyright (c) 2019 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "global.h"
#include "xzip.h"

class Utils : public QObject
{
    Q_OBJECT

public:
    struct STATS
    {
        QString sModule;
        qint32 nTotalModule;
        qint32 nCurrentModule;
        QString sFile;
        qint32 nTotalFile;
        qint32 nCurrentFile;
    };

    struct RECORD
    {
        QString sFullPath;
        QString sPath;
        bool bIsFile;
    };

    struct INSTALL_RECORD
    {
        QString sFullPath;
        QString sPath;
        bool bIsFile;
        QString sSHA1;
    };

    struct REMOVE_RECORD
    {
        QString sFullPath;
        QString sPath;
        bool bIsFile;
    };

    struct MDATA
    {
        QString sName;
        QString sCurrentVersion;
        QString sLastVersion;
        bool bIs32;
        bool bIs64;
        QString sCurrentDate;
        QString sLastDate;
        QString sAuthor;
        QString sBugreport;
        QString sInfo;
        QString sRoot;
        QString sBundleFileName;
        QList<Utils::INSTALL_RECORD> listInstallRecords;
        QList<Utils::REMOVE_RECORD> listRemoveRecords;
        qint64 nSize;
        qint64 nCompressedSize;
    };

    struct FILE_RECORD
    {
        QString sFullPath;
        QString sPath;
        QString sSHA1;
//        qint64 nSize;
//        qint64 nCompressedSize;
    };

    struct DIRECTORY_RECORD
    {
        QString sFullPath;
        QString sPath;
    };

    struct WEB_RECORD
    {
        QString sFileName;
        QString sLink;
    };

    explicit Utils(QObject *parent=nullptr);

    static QList<RECORD> getRecords(QString sRootPath);
    static bool checkMData(MDATA *pMData,QString *psErrorString);
    static QString createBundleName(MDATA *pMData);
    static bool isPluginValid(QString sFileName);
    static bool isPluginValid(QIODevice *pDevice);

    static QByteArray createPluginInfo(Utils::MDATA *pMData,QList<Utils::FILE_RECORD> *pListFileRecords,QList<Utils::DIRECTORY_RECORD> *pListDirectoryRecords,QString sSHA1);
    static MDATA getMDataFromZip(QString sFileName,QString sRootPath);
    static MDATA getMDataFromZip(QIODevice *pDevice,QString sRootPath);
    static MDATA getMDataFromData(QByteArray baData, QString sRootPath);
    static MDATA getMDataFromJSONFile(QString sFileName, QString sRootPath);

    static QList<MDATA> getInstalledModules(QString sDataPath,QString sRootPath);
    static QList<MDATA> getModulesFromJSONFile(QString sFileName);

    static QList<MDATA> mergeMData(QList<MDATA> *pList1,QList<MDATA> *pList2);

private:
    static void _getRecords(QString sRootPath,QString sCurrentPath,QList<RECORD> *pListRecords);
};

#endif // UTILS_H
