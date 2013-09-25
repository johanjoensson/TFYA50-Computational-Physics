CC = pdflatex

FILE = project_plan.tex

OUTPUT = $(FILE:tex=pdf)

AUX = $(FILE:tex=aux)
TOC = $(FILE:tex=toc)
LOG = $(FILE:tex=log)

TEMP = $(AUX) $(TOC) $(LOG)

.PHONY:	all,clean,cleanall

all:	$(OUTPUT)

%.pdf:	%.tex
# In order to make sure that everything gets compiled correctly (references, 
# table of contents, tags etc) you need to compile a minimum of 2 times, I do
# 3 just to be sure
	for counter in 1 2 3 ; do \
		pdflatex $(FILE) ; \
	done

view:	$(OUTPUT)
	qpdfview $^

clean:	
	rm  $(TEMP)

cleanall:
	rm $(OUTPUT) $(TEMP)
