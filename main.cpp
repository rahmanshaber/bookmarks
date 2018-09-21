/*
Bookmarks app for bookmarking files

Bookmarks is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see {http://www.gnu.org/licenses/}. */

#include "bookmarks.h"

#include <QApplication>
#include <QFont>
#include <QStyleFactory>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <cprime/utilities.h>
#include <cprime/settingsmanage.h>


void startSetup()
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // set all the requried folders
    Utilities::setupFileFolder(Utilities::FileFolderSetup::BookmarkFolder);
    Utilities::setupFileFolder(Utilities::FileFolderSetup::DriveMountFolder);
    Utilities::setupFileFolder(Utilities::FileFolderSetup::TrashFolder);
    Utilities::setupFileFolder(Utilities::FileFolderSetup::MimeFile);


    // if setting file not exist create one with defult
    SettingsManage sm;
    sm.createDefaultSettings();

    // set a icon across all the apps
    QIcon::setThemeName(sm.getThemeName());

    // set one font style across all the apps
    QFont fl (sm.getFontStyle(), 10, QFont::Normal);
    QApplication::setFont(fl);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_EnableHighDpiScaling);
    app.setQuitOnLastWindowClosed(true);

    startSetup();

    // Set application info
    app.setOrganizationName("CoreBox");
    app.setApplicationName("Bookmarks");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( QCommandLineOption( QStringList( ) << "bookIt", "Bookmark file" ) );

    const QString files = "[FILE1, FILE2,...]";
    parser.addPositionalArgument("files", files, files);

    parser.process(app);

    QStringList args = parser.positionalArguments();

    QStringList paths;
    foreach (QString arg, args) {
      QFileInfo info(arg);
      paths.push_back(info.absoluteFilePath());
    }

    bookmarks *bk = new bookmarks;

    if ( parser.isSet( "bookIt" ) ) {
        bk->sendFiles(paths);
    } else {
        bk->show( );
    }

    return app.exec();
}

