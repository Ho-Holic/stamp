// self
#include "ExtractOperation.h"
#include "io.h"

// chunck of incorrect arch. Actions must run simple tasks and not inserting bindings.
// Find a way to workaround this
#include "state/VariableBindingSingletone.h"

stamp::ExtractOperation::ExtractOperation()
    : Operation()
{
    //
}

void stamp::ExtractOperation::execute(const QStringList& arguments)
{

    const QString& resourceFilePath = arguments.at(ResourceFilePathIndex);
    const QString& saveFilePath = arguments.at(SaveFilePathIndex);

    QString fileAsString = io::getFileAsString(resourceFilePath);

    stamp::VariableBindingSingletone& binding = stamp::VariableBindingSingletone::getInstance();
    binding.replaceVariablesIn(fileAsString);

    io::saveStringAsFile(fileAsString, saveFilePath);
}

QStringList::size_type stamp::ExtractOperation::minimumArgumentCount() const
{
    return ArgumentSize;
}

QString stamp::ExtractOperation::usageString() const
{
    return "extract %{stampTemplatesPath}/resource/file/path/file.txt some/destination/dir";
}
