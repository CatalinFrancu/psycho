# texfot suppresses a lot of uninteresting output from pdflatex
pdf:
	TEXINPUTS=tex/:$TEXINPUTS: texfot pdflatex -halt-on-error psycho.tex

clean:
	rm -f *~ *.aux psycho.{dvi,log,out,toc}
