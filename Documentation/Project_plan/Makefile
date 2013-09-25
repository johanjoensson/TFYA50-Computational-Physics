CC = pdflatex

MAIN_FILE = project_plan.tex

SECTIONS = 	priorities.tex\
		project_phases.tex\
		priorities.tex\
		quality_plan.tex\
		training_plan.tex\

BASE_DEF = LIPS.tex

FILES = $(MAIN_FILE) $(BASE_DEF) $(SECTIONS)

OUTPUT = $(MAIN_FILE:tex=pdf)

AUX = $(FILES:tex=aux)
TOC = $(FILES:tex=toc)
LOG = $(FILES:tex=log)

TEMP = $(AUX) $(TOC) $(LOG)

.PHONY:	all,clean,cleanall

all:	$(OUTPUT)

%.pdf:	%.tex
# In order to make sure that everything gets compiled correctly (references, 
# table of contents, tags etc) you need to compile a minimum of 2 times, I do
# 3 just to be sure
	for counter in 1 2 3 ; do \
		$(CC) $(FILES) ; \
	done

view:	$(OUTPUT)
	qpdfview $^

clean:	
	rm  $(TEMP)

cleanall:
	rm $(OUTPUT) $(TEMP)
