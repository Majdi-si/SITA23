COMPILE = ocamlc
COMPILEOPT = ocamlopt
CSLDEP=ocamldep
CAMLLEX=ocamllex
CAMLYACC=ocamlyacc
CAMLDOC= ocamldoc

ASTAR_PATH= ../..
INCLUDES= -I $(ASTAR_PATH)/

NORM_FILES= geo.ml problem.ml options.ml pathfinder.ml main.ml
NORM_OBJS =  $(NORM_FILES:.ml=.cmo)
OPT_OBJS=  $(NORM_FILES:.ml=.cmx)

LIBS= unix.cma $(ASTAR_PATH)/a_star.cma

all : findpath findpath.norm doc

doc:
	mkdir doc;$(CAMLDOC) $(INCLUDES) -html -t "PathFinder" -d doc -intro Intro -hide Pervasives *.mli

findpath.norm : $(NORM_OBJS)
	$(COMPILE) $(INCLUDES) -o $@ $(LIBS) $(NORM_OBJS)

findpath : $(OPT_OBJS)
	$(COMPILEOPT) $(INCLUDES) -o $@ $(LIBS:.cma=.cmxa) $(OPT_OBJS)

.SUFFIXES: .mll .mly .ml .mli .cmo .cmi .cmx

.mll.mli:
	$(CAMLLEX) $<
.mll.ml:
	$(CAMLLEX) $<
.mly.mli:
	$(CAMLYACC) $<
.mly.ml:
	$(CAMLYACC) $<
.ml.cmo :
	$(COMPILE) $(INCLUDES) -c $<
.mli.cmi :
	$(COMPILE) $(INCLUDES) -c $<
.ml.cmx :
	$(COMPILEOPT) $(INCLUDES) -c $<

cleandoc:
	\rm -Rf doc

clean:
	\rm -f *.cmo *.cmi *.cmx *.o *.a *.cma *.cmxa .depend *~ parser.ml parser.mli lexer.ml lexer.mli findpath.norm findpath

.depend:
	$(CSLDEP) $(INCLUDES) *.mli *.ml >.depend

include .depend
