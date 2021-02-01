// self
#include "Operation.h"

// arch
#include <QTextStream>

stamp::Operation::Operation()
{
    //
}

stamp::Operation::~Operation()
{
    //
}

QStringList stamp::Operation::escapeSplit(const QString& argString)
{
    static QChar QUOTION_MARK = '"';

    QStringList list;
    QString buffer;

    enum Mode { Normal,
        Escape };

    Mode mode = Normal;

    for (QString::const_iterator i = argString.begin(); i != argString.end(); ++i) {

        const QChar c = *i;

        switch (mode) {
        case Normal:
            if (c == QUOTION_MARK) {
                mode = Escape;
            } else if (c.isSpace()) {
                if (!buffer.isEmpty())
                    list.push_back(buffer);
                buffer.clear();
            } else {
                buffer += c;
            }
            break;
        case Escape:
            if (c == QUOTION_MARK) {
                mode = Normal;
            } else {
                buffer += c;
            }
            break;
        }
    }
    // no whitespace in the end, we need to add last element
    if (!buffer.isEmpty())
        list.push_back(buffer);
    buffer.clear();
    return list;
}

void stamp::Operation::splitArguments(const QStringList& arguments,
    stamp::ArgumentPairList& named,
    QStringList& noname)
{
    const QChar EQUAL_SYMBOL = '=';

    // make split functions
    for (const QString& arg : arguments) {
        if (arg.contains(EQUAL_SYMBOL)) {

            QStringList splited = arg.split(EQUAL_SYMBOL);

            // splited.size() != 2, two is value for left and right arguments in equals syntax "flag=value"
            if (splited.size() == 2) {
                named.push_back(qMakePair(splited.at(0), splited.at(1)));
            } else {
                QTextStream out(stdout);
                out << "Incorrect argument syntax." << Qt::endl;
            }
        } else {
            noname.push_back(arg);
        }
    }
}

void stamp::Operation::tryExecute(const QStringList& arguments)
{
    QTextStream out(stdout);

    if (arguments.size() >= minimumArgumentCount()) {
        execute(arguments);
    } else {
        out << QString("Incorrect argument count.") << Qt::endl
            << usageString() << Qt::endl;
    }
}
