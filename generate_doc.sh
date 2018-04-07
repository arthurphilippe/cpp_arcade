rm -fr doc
mkdir doc
git clone git@github.com:arthurphilippe/cpp_arcade.wiki.git
cd cpp_arcade.wiki
pandoc --from gfm Data-Types.md -o ../doc/Data-Types.pdf --pdf-engine=xelatex
pandoc --from gfm How-to-implement-a-graphical-interface.md -o ../doc/How-to-implement-a-graphical-interface.pdf --pdf-engine=xelatex
pandoc --from gfm How-to-implement-a-game.md -o ../doc/How-to-implement-a-game.pdf --pdf-engine=xelatex
rm -fr cpp_arcade.wiki
