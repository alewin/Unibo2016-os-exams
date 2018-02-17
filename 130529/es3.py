import os, sys

if len(sys.argv) != 2:
    print("The function requires one argument to be passed in.")
    exit()
if not os.path.isdir(sys.argv[1]):
    print("The function requires a directory.")
    exit()


rootdir = sys.argv[1]
result = {}
for dirPath, dirNames, files in os.walk(rootdir):
    for f in files:
        filename, file_extension = os.path.splitext(f)
        if file_extension in result.keys():
            result[file_extension] += os.path.getsize(f)
        else:
            result[file_extension] = os.path.getsize(f);

print result
"""

def GetSize(topDir, extensionSize):
    for dirPath, dirNames, files in os.walk(topDir):
        for file in files:
            # 'example.mp3' -> ['example', 'mp3']
            # 'example.tar.gz' -> ['example', 'tar', 'gz']
            parts = file.split('.')
            # ['example', 'mp3'] -> ['mp3']
            # ['example', 'tar', 'gz'] -> ['tar', 'gz']
            parts = parts[1:]
            # ['mp3'] -> '.mp3'
            # ['tar', 'gz'] -> '.tar.gz'
            fileExtension = ".{0}".format(".".join(str(part) for part in parts))

            # Compute the size in Bytes and update the dictionary
            filePath = os.path.join(dirPath, file)
            fileSize = os.path.getsize(filePath)
            extensionSize[fileExtension] = extensionSize.get(fileExtension, 0) + fileSize

# Print results
def PrintResults(extensionSize):
    for key, value in sorted(extensionSize.items()):
        print('{0}: {1} Bytes.'.format(key, value))

if __name__ == "__main__":
    sys.exit(Main(sys.argv))
"""
