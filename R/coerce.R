# coerce.R - DESC
# /coerce.R

# Copyright European Union, 2016
# Author: Iago Mosqueira (EC JRC) <iago.mosqueira@ec.europa.eu>
#
# Distributed under the terms of the European Union Public Licence (EUPL) V.1.1.

#' Methods for coercing objects between classes
#'
#' A call to *as(from, 'to')* will coerce the object *from*, of a certain class,
#' to one of class *to*, as specified in the method.
#'
#' An object of class *FLQuants* can be coerced into a *fwdControl*, through a
#' call to *as.data.frame*. The name of the element, or elements, in the object
#' specifies the 'quant' in *fwdControl*. The 'quant' in the *FLQuant* object, the
#' name of the first dimension, is ignored unles is one of 'min', 'value' or 'max'.
#' See the examples below on how to pass one or more *FLQuant* objects to *fwd*.
#'
#' @param from Object to be coerced into one of another class.
#' @param to Name of the output class, *character*.
#'
#' @return An object of the requested class.
#'
#' @name coerce
#' @rdname coerce
#'
#' @author Iago Mosqueira. EC JRC.
#' @seealso [coerce]
#' @keywords methods
#' @md
NULL

# FLQuants -> fwdControl {{{

#' @name coerce
#' @rdname coerce
#' @examples
#' # Single *catch* target
#' as(FLQuants(catch=FLQuant(4500, dimnames=list(year=2000))), "fwdControl")
#' # Single single *f* range
#' as(FLQuants(f=FLQuant(c(0.1, 0.9),
#'   dimnames=list(quant=c("min", "max"), year=2000))), 'fwdControl')
#' # Single *f* target, *value* specified
#' as(FLQuants(f=FLQuant(0.5, dimnames=list(quant=c("value"), year=2000))),
#'   'fwdControl')
#' # *catch* and *ssb* targets
#' as(FLQuants(catch=FLQuant(4500, dimnames=list(year=2000)),
#'    ssb_end=FLQuant(12000, dimnames=list(year=2000))), "fwdControl")
#' # *f* target and *catch* limits
#' as(FLQuants(f=FLQuant(0.5, dimnames=list(year=2000)),
#'   catch=FLQuant(c(100, 4000), dimnames=list(quant=c("min", "max"), year=2000))),
#'   'fwdControl')
#' # *f* target and *catch* minimum
#' as(FLQuants(f=FLQuant(0.5, dimnames=list(year=2000)),
#'   catch=FLQuant(c(100), dimnames=list(quant=c("min"), year=2000))), 'fwdControl')
setAs("FLQuants", "fwdControl",
  function(from) {
    
    # GET 'quant'
    qua <- quant(from[[1]])

		# CONVERT
    df <- as.data.frame(from)[,c(qua, "year", "iter",
      "data", "qname", "season")]
    
    # RESHAPE if min/max in quant
    if(any(df[,qua] %in% c("min", "max", "value"))) {
      df[,qua][df[,qua] == "all"] <- "value"
      df <- reshape(df, idvar = c("year", "iter", "qname", "season"),
      timevar = qua, direction = "wide")
      names(df) <- gsub("data.", "", names(df))
    # or RENAME data as value
    } else {
      df[, qua] <- NULL
      names(df) <- sub("data", "value", names(df))
    }

    # RENAME qname to quant
    names(df) <- sub("qname", "quant", names(df))

    # DROP season if not used
    if(length(unique(df$season)) == 1)
      df$season <- NULL

    its <- dim(from[[1]])[6]

		# NO ITERS
		if(its == 1) {

      target <- cbind(df[,-2], fishery=as.numeric(NA), catch=as.numeric(NA),
        biol=1)

      return(fwdControl(target))

    # ITERS
		} else {

			target <- cbind(df[df$iter == df$iter[1],][,c('year', 'quant')])

			iters <- array(NA, dim=c(dim(target)[1], 3, its),
        dimnames=list(seq(dim(target)[1]), c("min", "value", "max"), iter=dimnames(from[[1]])$iter))
                   
			iters[,"value",] <- c(from[[1]])
      
      target <- cbind(target, fishery=as.numeric(NA), catch=as.numeric(NA),
        biol=1)
			
			return(fwdControl(target=target, iters=iters))
		}
} ) # }}}

# FLBiol -> FLBiolcpp list {{{
setAs("FLBiol", "list",
  function(from) {

    list(
      biol = as(from, "FLBiolcpp"),
      srr_deviances = FLQuant(),
      srr_deviances_mult = TRUE)
  }) # }}}
