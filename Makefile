# texfot suppresses a lot of uninteresting output from pdflatex
pdf:
	TEXINPUTS=tex/:$TEXINPUTS: texfot pdflatex -halt-on-error -shell-escape psycho.tex

clean:
	rm -rf *~ *.aux psycho.{dvi,log,out,toc} _minted-psycho
