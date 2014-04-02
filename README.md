antialiasing recovery
=====================

description
-----------

Performing some kind of non-linear filters on images often induces aliasing, this program implements the method described in this [paper](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&cad=rja&ved=0CDMQFjAB&url=http%3A%2F%2Fresearch.microsoft.com%2Fen-us%2Fum%2Fpeople%2Fhoppe%2Faarecovery.pdf&ei=QamXUrP6AZLboAT9xoDoDQ&usg=AFQjCNFLZrX_vNVlN2ShAQOIZCeP6P3M-Q&sig2=23TBu1tviZZseSq09keNtg&bvm=bv.57155469,d.cGU) which helps to recover images damaged by some kind of non-linear filters. It is performed as an adjustment of gradients in some regions that were potentially damaged in the filtered image.

run
---

Images should be PPM format 24 bits.
The program is looking for images from the media/ folder which should
be located in the working directory.

```bash
./aarecovery.out -o original [-f filtered] # filenames without 
extension
````

results
-------

The following images were zoomed to assess the results.
 
Original image:

![original](https://bitbucket.org/cewxel/aarecovery/wiki/aa_original.png)

Non-linear filter performed on it (here simple thresholding):

![original](https://bitbucket.org/cewxel/aarecovery/wiki/aa_filtered.png)

The result of performing anti-aliasing recovery:

![original](https://bitbucket.org/cewxel/aarecovery/wiki/aa_recovered.png)
