#include "pgmloader.h"

PGMImage PGMLoader::load(std::string filename) {
    int width, length, grayscale;
    char* memblock; 
    std::string path = MEDIA_PATH + filename + PGM_EXT;
    std::string line1;
    std::string line2;
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    std::ifstream::pos_type start, end, size;
    std::ifstream::off_type newStart;
    
    if(!file) {
        throw std::runtime_error("Can't open file" + path);
    }   

    std::cout << "Reading " << path << std::endl;

    getline(file, line1);
    getline(file, line2);

    std::cout << "Header: " << std::endl;
    std::cout << line1 << std::endl;
    std::cout << line2 << std::endl;

    file >> width;
    file >> length;
    file >> grayscale;

    std::cout << "Width: " << width << ", Length: " << length << std::endl;
    std::cout << "Grayscale: " << grayscale << std::endl;

    PGMImage image(length, width, grayscale);

    start = file.tellg();
    file.seekg (0, std::ios::end);
    end = file.tellg();
    size = end - start;
    memblock = new char[size];
    newStart = static_cast<std::ifstream::off_type>(start);
    file.seekg(newStart, std::ios::beg);
    file.read(memblock, size);

    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < width; ++j) {
            image(i, j) = static_cast<float>((unsigned char)memblock[i*length+j]);
        }   
    }

    delete[] memblock;
    file.close();

    return image;
}

void PGMLoader::save(PGMImage& pgmimage, std::string filename) {
    std::string path = MEDIA_PATH + filename + PGM_EXT;
    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary);

    if(file.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);

        file << "P5\n";
        file << "# " << dt;
        file << pgmimage.getLength() << " " << pgmimage.getWidth() << "\n";
        file << pgmimage.getGrayscale() << "\n";

        for(int i = 0; i < pgmimage.getLength(); ++i) {
            for(int j = 0; j < pgmimage.getWidth(); ++j) {
                file << static_cast<char>(pgmimage(i, j));
            }
        }

        file.close();
        std::cout << "Saved file " << path << std::endl;
    }
}
