<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="node()|@*">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>
<!-- -->



<xsl:template match="ssn/@minrep">
	<xsl:attribute name="minrep"><xsl:value-of select="$numofReps"/></xsl:attribute>  
</xsl:template>

<xsl:variable name="numofReps">
<xsl:choose>
	<xsl:when test="ssn/@MinPart_S = 'at least 75% of the questions'">
        <xsl:value-of select="(floor((count(ssn/p[@isDel='N']) * 3) div 4))"/>
    </xsl:when>

    <xsl:when test="ssn/@MinPart_S = 'at least 50% of the questions'">
	<xsl:value-of select="(floor((count(ssn/p[@isDel='N']) * 1) div 2))"/>
	</xsl:when>

	<xsl:when test="ssn/@MinPart_S = '100% of questions'">
		<xsl:value-of select="count(ssn/p[@isDel='N'])"/>
	</xsl:when>

	<xsl:when test="ssn/@MinPart_S = 'all but one question'">
		<xsl:value-of select="count(ssn/p[@isDel='N'])-1"/>
	</xsl:when>

	<xsl:when test="ssn/@MinPart_S = 'at least one question'">
		<xsl:value-of select="1"/>
	</xsl:when>

	<xsl:otherwise>
        <xsl:value-of select="ssn/@minrep"/>
    </xsl:otherwise>
</xsl:choose>

</xsl:variable>
<xsl:variable name="minrep">
<xsl:value-of select="$numofReps"/>
</xsl:variable>

	<!--
<xsl:value-of select="(floor(($numofReps * 3) div 4))"/>

	$<xsl:value-of select="format-number(//Applications/AveAnnualVolume div 12,'###,###,##0.00')"/> 
	<xsl:value-of select="concat('ass ', 'ssn/@MinPart_S')"/>
	-
"at least 75% of the questions"
"all but one question"
"at least one question"
"at least 50% of the questions"
"100% of questions"


        { retValue = "all but one question"; }
        else if((partReq > 1) && (partReq < 39))
        { retValue = "at least one question"; }
        else if((partReq > 39) && (partReq <= 50))
        { retValue = "at least 50% of the questions"; }
        else if((partReq > 95) && (partReq <= 100))
        { retValue = "100% of questions"; }
	-->	


</xsl:stylesheet>